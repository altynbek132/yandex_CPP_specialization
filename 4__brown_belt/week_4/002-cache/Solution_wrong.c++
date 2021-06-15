#include <bits/stdc++.h>
#include "Common.h"

using namespace std;
// DO NOT WORK - DO NOT KNOW WHY
class LruCache : public ICache {
   public:
    using CacheType = list<BookPtr>;
    using MapType = unordered_map<string, CacheType::iterator>;

   public:
    LruCache(shared_ptr<IBooksUnpacker> books_unpacker, const Settings& settings)
        : books_unpacker_(move(books_unpacker)), settings_(settings) {}

    BookPtr GetBook(const string& book_name) override {
        bool found = false;
        auto name_to_cacheIt_it = [&] {
            lock_guard g(m_);
            auto it = name_to_cacheIt_.find(book_name);
            found = it != name_to_cacheIt_.end();
            return it;
        }();

        if (!found) {
            auto book_ptr_uniq = books_unpacker_->UnpackBook(book_name);
            auto& book = *book_ptr_uniq;
            size_t book_size = CalcSize(book);
            if (book_size > settings_.max_memory) {
                return move(book_ptr_uniq);
            }

            BookPtr book_ptr = move(book_ptr_uniq);

            if (memory_used_by_books_ + book_size > settings_.max_memory) {
                Shrink(book_size);
            }

            {
                lock_guard g(m_);
                auto cache_it = cache_.insert(cache_.begin(), book_ptr);
                name_to_cacheIt_.insert(name_to_cacheIt_it, {book.GetName(), cache_it});
            }
            memory_used_by_books_ += book_size;
            return book_ptr;
        }

        auto& book_ptr = *(name_to_cacheIt_it->second);
        auto& book = *book_ptr;
        {
            // move cache_ piece to front as recent
            lock_guard g(m_);
            auto cache_it = name_to_cacheIt_it->second;
            cache_.splice(cache_.begin(), cache_, cache_it);
            name_to_cacheIt_.insert(name_to_cacheIt_it, {book.GetName(), cache_it});
        }
        return book_ptr;
    }

   private:
    atomic<size_t> memory_used_by_books_ = 0;
    shared_ptr<IBooksUnpacker> books_unpacker_;
    Settings settings_;
    mutex m_;

    CacheType cache_;
    MapType name_to_cacheIt_;

    void Shrink(size_t needed_size) {
        lock_guard g(m_);
        while (needed_size > settings_.max_memory - memory_used_by_books_) {
            auto& book = **cache_.rbegin();
            size_t book_size = CalcSize(book);

            name_to_cacheIt_.erase(book.GetName());
            cache_.pop_back();

            memory_used_by_books_ -= book_size;
        }
    }

    static size_t CalcSize(const IBook& book) {
        return /*book.GetName().size() + */ book.GetContent().size();
    }
};

unique_ptr<ICache> MakeCache(shared_ptr<IBooksUnpacker> books_unpacker, const ICache::Settings& settings) {
    return make_unique<LruCache>(move(books_unpacker), settings);
}

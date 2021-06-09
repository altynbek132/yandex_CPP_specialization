#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO
#include "test_runner.h"

#include <forward_list>
#include <iterator>

using namespace std;

template <typename It, typename Type>
It find_prev(It begin, It end, const Type& value) {
    auto prev = begin;
    for (auto it = begin; it != end; ++it) {
        if (*it == value) {
            return prev;
        }
        prev = it;
    }
    return end;
}

template <typename Type, typename Hasher>
class HashSet {
   public:
    using BucketList = forward_list<Type>;

    explicit HashSet(size_t num_buckets, Hasher hasher = {}) : buckets(num_buckets), hasher(move(hasher)) {}
    void Add(const Type& value) {
        if (Has(value)) {
            return;
        }
        forward_list<Type>& bucket = GetBucket_(value);
        bucket.push_front(value);
    }
    bool Has(const Type& value) const {
        const forward_list<Type>& bucket = GetBucket_(value);
        return find(bucket.begin(), bucket.end(), value) != bucket.end();
    }
    void Erase(const Type& value) {
        forward_list<Type>& bucket = GetBucket_(value);

        auto it_prev = find_prev(bucket.begin(), bucket.end(), value);
        if (it_prev == bucket.end()) {
            return;
        }
        if (it_prev == bucket.begin() && *it_prev == value) {
            bucket.pop_front();
            return;
        }
        bucket.erase_after(it_prev);
    }
    const BucketList& GetBucket(const Type& value) const { return GetBucket_(value); }

   private:
    vector<BucketList> buckets;
    Hasher hasher;

    BucketList& GetBucket_(const Type& value) {
        auto hash_value = hasher(value);
        return buckets[hash_value % buckets.size()];
    }
    const BucketList& GetBucket_(const Type& value) const {
        auto hash_value = hasher(value);
        return buckets[hash_value % buckets.size()];
    }
};

struct IntHasher {
    size_t operator()(int value) const {
        // Это реальная хеш-функция из libc++, libstdc++.
        // Чтобы она работала хорошо, std::unordered_map
        // использует простые числа для числа бакетов
        return value;
    }
};

struct TestValue {
    int value;

    bool operator==(TestValue other) const { return value / 2 == other.value / 2; }
};

struct TestValueHasher {
    size_t operator()(TestValue value) const { return value.value / 2; }
};

void TestSmoke() {
    HashSet<int, IntHasher> hash_set(2);
    hash_set.Add(3);
    hash_set.Add(4);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Erase(3);

    ASSERT(!hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Add(3);
    hash_set.Add(5);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(hash_set.Has(5));
}

void TestEmpty() {
    HashSet<int, IntHasher> hash_set(10);
    for (int value = 0; value < 10000; ++value) {
        ASSERT(!hash_set.Has(value));
    }
}

void TestIdempotency() {
    HashSet<int, IntHasher> hash_set(10);
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
}

void TestEquivalence() {
    HashSet<TestValue, TestValueHasher> hash_set(10);
    hash_set.Add(TestValue{2});
    hash_set.Add(TestValue{3});

    ASSERT(hash_set.Has(TestValue{2}));
    ASSERT(hash_set.Has(TestValue{3}));

    const auto& bucket = hash_set.GetBucket(TestValue{2});
    const auto& three_bucket = hash_set.GetBucket(TestValue{3});
    ASSERT_EQUAL(&bucket, &three_bucket);

    ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
    ASSERT_EQUAL(2, bucket.front().value);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSmoke);
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestIdempotency);
    RUN_TEST(tr, TestEquivalence);
    return 0;
}

#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO
#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

size_t pow_size_t(size_t x, size_t p) {
    if (p == 0)
        return 1;
    if (p == 1)
        return x;

    size_t tmp = pow_size_t(x, p / 2);
    if (p % 2 == 0)
        return tmp * tmp;
    else
        return x * tmp * tmp;
}

size_t PolynomicCombine(size_t x, const vector<size_t> v) {
    size_t res = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        res += pow_size_t(x, v.size() - 1 - i) * v[i];
    }
    return res;
}

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;

    bool operator==(const Record& rhs) const {
        return id == rhs.id && title == rhs.title && user == rhs.user && timestamp == rhs.timestamp &&
               karma == rhs.karma;
    }
    bool operator!=(const Record& rhs) const { return !(rhs == *this); }

    bool operator<(const Record& rhs) const {
        return std::tie(id, title, user, timestamp, karma) <
               std::tie(rhs.id, rhs.title, rhs.user, rhs.timestamp, rhs.karma);
    }
    bool operator>(const Record& rhs) const { return rhs < *this; }
    bool operator<=(const Record& rhs) const { return !(rhs < *this); }
    bool operator>=(const Record& rhs) const { return !(*this < rhs); }
};

namespace std {
template <>
struct hash<Record> {
    hash<string> string_hash;
    hash<int> int_hash;
    size_t operator()(const Record& obj) const {
        static const size_t x = 228'1488 + 54'27;
        size_t r1 = string_hash(obj.id);
        size_t r2 = string_hash(obj.title);
        size_t r3 = string_hash(obj.user);
        size_t r4 = int_hash(obj.timestamp);
        size_t r5 = int_hash(obj.karma);
        return PolynomicCombine(x, {r1, r2, r3, r4, r5});
    }
};
}  // namespace std

// Реализуйте этот класс
class Database {
   public:
    struct Entry;

    using IdToRecords = unordered_map<string, Entry>;
    using TimestampToRecords = multimap<int, Record&>;
    using KarmaToRecords = multimap<int, Record&>;
    using UserToRecords = unordered_multimap<string, Record&>;
    using RecordsCollection = list<Record>;

    struct Entry {
        Record& record;
        // iterators:
        RecordsCollection::iterator records_data_it;

        TimestampToRecords::iterator timestamp_to_record_it;
        KarmaToRecords::iterator karma_to_record_it;
        UserToRecords::iterator user_to_record_it;
    };

    bool Put(const Record& record) {
        auto it = id_to_record_entry.find(record.id);
        if (it != id_to_record_entry.end()) {
            return false;
        }
        auto records_data_it = records_data.insert(records_data.end(), record);
        auto& value = *records_data_it;

        auto timestamp_to_record_it = timestamp_to_record.insert({value.timestamp, value});
        auto karma_to_record_it = karma_to_record.insert({value.karma, value});
        auto user_to_record_it = user_to_record.insert({value.user, value});

        id_to_record_entry.insert(it, {value.id, Entry{value, records_data_it, timestamp_to_record_it,
                                                       karma_to_record_it, user_to_record_it}});
        return true;
    }
    const Record* GetById(const string& id) const {
        auto it = id_to_record_entry.find(id);
        if (it == id_to_record_entry.end()) {
            return nullptr;
        }
        return &(it->second.record);
    }
    bool Erase(const string& id) {
        auto it = id_to_record_entry.find(id);
        if (it == id_to_record_entry.end()) {
            return false;
        }
        auto& entry = id_to_record_entry.at(id);
        timestamp_to_record.erase(entry.timestamp_to_record_it);
        karma_to_record.erase(entry.karma_to_record_it);
        user_to_record.erase(entry.user_to_record_it);
        records_data.erase(entry.records_data_it);
        id_to_record_entry.erase(it);
        return true;
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        auto begin = timestamp_to_record.lower_bound(low);
        auto end = timestamp_to_record.upper_bound(high);
        processSequence(begin, end, callback);
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        auto begin = karma_to_record.lower_bound(low);
        auto end = karma_to_record.upper_bound(high);
        processSequence(begin, end, callback);
    }

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const {
        auto [begin, end] = user_to_record.equal_range(user);
        processSequence(begin, end, callback);
    }

   private:
    RecordsCollection records_data;
    IdToRecords id_to_record_entry;

    TimestampToRecords timestamp_to_record;
    KarmaToRecords karma_to_record;
    UserToRecords user_to_record;

    template <typename Callback, typename It>
    static void processSequence(It begin, It end, Callback callback) {
        for (auto it = begin; it != end; ++it) {
            if (!callback(it->second)) {
                return;
            }
        }
    }
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}

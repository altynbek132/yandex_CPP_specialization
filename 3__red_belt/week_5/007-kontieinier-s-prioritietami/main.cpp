#include <bits/stdc++.h>
#include <profile.h>
#include <test_runner.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    freopen("input.txt", "r", stdin);
    return;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("output.txt", "w", stdout);
}

struct Prerun {
    Prerun() {
        txt();
        TestAll();
    }
};

Prerun maslo;
#endif
// ==========================================

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include "test_runner.h"

using namespace std;

template <typename T>
class PriorityCollection {
   public:
    using Id = int;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object);

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin,
             ObjInputIt range_end,
             IdOutputIt ids_begin);

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const;

    // Получить объект по идентификатору
    const T& Get(Id id) const;

    // Увеличить приоритет объекта на 1
    void Promote(Id id);

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const;

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax();

   private:
    // Приватные поля и методы
    Id id_ = 0;
    map<Id, T> id_to_obj_;
    map<Id, int> id_to_priority_;
    map<int, set<Id>> priority_to_ids_;
};

template <typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::Add(T object) {
    id_to_obj_[id_] = std::move(object);
    int priority = 0;
    id_to_priority_[id_] = priority;
    priority_to_ids_[priority].insert(id_);
    return Id(id_++);
}

template <typename T>
template <typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin,
                                ObjInputIt range_end,
                                IdOutputIt ids_begin) {
    while (range_begin != range_end) {
        *ids_begin++ = Add(std::move(*range_begin++));
    }
}

template <typename T>
bool PriorityCollection<T>::IsValid(PriorityCollection::Id id) const {
    return id_to_obj_.count(id);
}

template <typename T>
const T& PriorityCollection<T>::Get(PriorityCollection::Id id) const {
    return id_to_obj_.at(id);
}

template <typename T>
void PriorityCollection<T>::Promote(PriorityCollection::Id id) {
    auto& priority = id_to_priority_[id];
    auto it_priority_to_ids = priority_to_ids_.find(priority);
    auto& ids = it_priority_to_ids->second;
    ids.erase(find(ids.begin(), ids.end(), id));
    if (ids.empty()) {
        priority_to_ids_.erase(it_priority_to_ids);
    }
    priority_to_ids_[++priority].insert(id);
}

template <typename T>
pair<const T&, int> PriorityCollection<T>::GetMax() const {
    Id id = *(priority_to_ids_.rbegin()->second.rbegin());
    return {id_to_obj_.at(id), id_to_priority_.at(id)};
}

template <typename T>
pair<T, int> PriorityCollection<T>::PopMax() {
    auto it_id = prev(priority_to_ids_.rbegin()->second.end());
    Id id = *it_id;
    auto it_id_to_obj = id_to_obj_.find(id);
    auto it_id_to_priority = id_to_priority_.find(id);

    pair<T, int> p(std::move(it_id_to_obj->second), it_id_to_priority->second);
    id_to_obj_.erase(it_id_to_obj);
    id_to_priority_.erase(it_id_to_priority);

    priority_to_ids_.rbegin()->second.erase(it_id);
    if (priority_to_ids_.rbegin()->second.empty()) {
        priority_to_ids_.erase(prev(priority_to_ids_.end()));
    }

    return p;
}

class StringNonCopyable : public string {
   public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    set<StringNonCopyable> asdf;

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}

// ==========================================

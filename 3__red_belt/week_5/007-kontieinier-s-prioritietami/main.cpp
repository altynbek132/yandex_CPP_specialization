// #include <bits/stdc++.h>
// #include "profile.h"
// #include "test_runner.h"
//
// using namespace std;
//
// #ifdef MASLO
//
// prerun maslo(true, false, false);
//
// #endif  // MASLO

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
    Id Add(T object) {
        Id new_id = objects.size();
        objects.push_back({move(object), 0});
        sorted_objects.insert({0, new_id});
        return new_id;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
        for (auto it = range_begin; it != range_end; ++it) {
            *ids_begin++ = Add(move(*it));
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return id >= 0 &&              //
               id < objects.size() &&  //
               objects[id].priority != NONE_PRIORITY;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const { return objects[id].data; }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        auto& item = objects[id];
        sorted_objects.erase({item.priority, id});
        sorted_objects.insert({++item.priority, id});
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const {
        auto [priority, id] = *sorted_objects.rbegin();
        return {objects[id].data, priority};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax() {
        auto it = sorted_objects.rbegin();
        auto [priority, id] = *it;
        auto& item = objects[id];
        sorted_objects.erase(--it.base());
        item.priority = NONE_PRIORITY;
        return {move(item.data), priority};
    }

   private:
    struct ObjectItem {
        T data;
        int priority = 0;
    };
    static const int NONE_PRIORITY = -1;

    vector<ObjectItem> objects;
    // pair of priority and id
    set<pair<int, Id>> sorted_objects;
};

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

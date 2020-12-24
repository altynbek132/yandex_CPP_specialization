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


#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;


template<typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    std::list<typename RandomIt::value_type> pool;
    std::copy(std::make_move_iterator(first), std::make_move_iterator(last), std::inserter(pool, pool.end()));
    auto cur_pos = pool.begin();
    
    while (!pool.empty()) {
        *(first++) = std::move(*cur_pos);
        cur_pos = pool.erase(std::move(cur_pos));
        
        for (int i = 0; i < step_size - 1; ++i) {
            if (cur_pos == pool.end()) { cur_pos = pool.begin(); }
            cur_pos = std::move(std::next(cur_pos));
            if (cur_pos == pool.end()) { cur_pos = pool.begin(); }
        }
    }
}

vector<int> MakeTestVector() {
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
  int value;
  
  NoncopyableInt(int value) : value(value) {}
  
  NoncopyableInt(const NoncopyableInt &) = delete;
  NoncopyableInt &operator=(const NoncopyableInt &) = delete;
  
  NoncopyableInt(NoncopyableInt &&) = default;
  NoncopyableInt &operator=(NoncopyableInt &&) = default;
};

bool operator==(const NoncopyableInt &lhs, const NoncopyableInt &rhs) {
    return lhs.value == rhs.value;
}

ostream &operator<<(ostream &os, const NoncopyableInt &v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});
    
    MakeJosephusPermutation(begin(numbers), end(numbers), 2);
    
    vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});
    
    ASSERT_EQUAL(numbers, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}


// ==========================================

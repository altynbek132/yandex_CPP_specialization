#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

#include "simple_vector.h"
#include "test_runner.h"

#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

void TestCopyAssignment() {
    SimpleVector<int> numbers(10);
    iota(numbers.begin(), numbers.end(), 1);

    SimpleVector<int> dest;
    SimpleVector<int> dest2;
    SimpleVector<int> dest3;
    ASSERT_EQUAL(dest.Size(), 0u);

    dest = numbers;
    dest2 = numbers;
    dest3 = numbers;
    ASSERT_EQUAL(dest.Size(), numbers.Size());
    ASSERT(dest.Capacity() >= dest.Size());
    ASSERT(equal(dest.begin(), dest.end(), numbers.begin()));
    ASSERT(equal(dest2.begin(), dest2.end(), numbers.begin()));
    ASSERT(equal(dest3.begin(), dest3.end(), numbers.begin()));
}

void TestConstruction() {
    SimpleVector<int> empty;
    ASSERT_EQUAL(empty.Size(), 0u);
    ASSERT_EQUAL(empty.Capacity(), 0u);
    ASSERT(empty.begin() == empty.end());

    SimpleVector<string> five_strings(5);
    ASSERT_EQUAL(five_strings.Size(), 5u);
    ASSERT(five_strings.Size() <= five_strings.Capacity());
    for (auto& item : five_strings) {
        ASSERT(item.empty());
    }
    five_strings[2] = "Hello";
    ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
    SimpleVector<int> v;
    for (int i = 10; i >= 1; --i) {
        v.PushBack(i);
        ASSERT(v.Size() <= v.Capacity());
    }
    sort(begin(v), end(v));

    const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQUAL(v.Size(), expected.size());
    ASSERT(equal(begin(v), end(v), begin(expected)));
}

void TestSelfASS() {
    SimpleVector<int> numbers(10);
    SimpleVector<int> safe(10);
    iota(numbers.begin(), numbers.end(), 1);
    iota(safe.begin(), safe.end(), 1);

    numbers = numbers;
    ASSERT(equal(begin(numbers), end(numbers), begin(safe)));
    numbers = move(numbers);
    ASSERT(equal(begin(numbers), end(numbers), begin(safe)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCopyAssignment);
    RUN_TEST(tr, TestConstruction);
    RUN_TEST(tr, TestPushBack);
    RUN_TEST(tr, TestSelfASS);
}

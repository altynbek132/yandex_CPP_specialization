#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

template <typename T>
class Deque {
   public:
    Deque() = default;
    bool Empty() const { return frontReverse.empty() && back.empty(); }
    size_t Size() const { return frontReverse.size() + back.size(); }

    T& operator[](size_t pos) { return AtMain(pos); }
    const T& operator[](size_t pos) const { return AtMain(pos); }

    // throws out_of_range if pos >= Size()
    T& At(size_t pos) {
        CheckIndex(pos);
        return AtMain(pos);
    }
    // throws out_of_range if pos >= Size()
    const T& At(size_t pos) const {
        CheckIndex(pos);
        return AtMain(pos);
    }

    const T& Front() const { return frontReverse.empty() ? back.front() : frontReverse.back(); }
    T& Front() { return frontReverse.empty() ? back.front() : frontReverse.back(); }

    const T& Back() const { return back.empty() ? frontReverse.front() : back.back(); }
    T& Back() { return back.empty() ? frontReverse.front() : back.back(); }

    void PushFront(const T& item) { frontReverse.push_back(item); }
    void PushBack(const T& item) { back.push_back(item); }

   private:
    T& AtMain(size_t pos) {
        size_t frontSize = frontReverse.size();
        if (pos < frontSize) {
            return frontReverse[frontSize - 1 - pos];
        }
        return back[pos - frontSize];
    }

    const T& AtMain(size_t pos) const {
        size_t frontSize = frontReverse.size();
        if (pos < frontSize) {
            return frontReverse.at(frontSize - 1 - pos);
        }
        return back.at(pos - frontSize);
    }

    void CheckIndex(size_t pos) const {
        if (pos >= Size()) {
            throw out_of_range("out of range, epta");
        }
    }

    vector<T> frontReverse, back;
    /* <- frontReverse|      back ->
     *   [front ......|..... back]
     * */
};

int main() {
    const Deque<int> asdf;
    asdf.At(0);
    return 0;
}

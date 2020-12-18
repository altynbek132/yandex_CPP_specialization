#pragma once
#include <bits/stdc++.h>

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    auto maxIt = last;
    while (first != last) {
        if (pred(*first) && (maxIt == last || *first > *maxIt)) {
            maxIt = first;
        }
        first++;
    }
    return maxIt;
}

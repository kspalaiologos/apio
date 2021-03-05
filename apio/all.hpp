
#ifndef _APIO_ALL
#define _APIO_ALL

#include <algorithm>

namespace apio {

template <typename Predicate, typename Iterator>
bool all(Predicate pred, Iterator begin, Iterator end) {
    for(; begin != end; ++begin)
        if(!pred(*begin))
            return false;
    return true;
}

}

#endif

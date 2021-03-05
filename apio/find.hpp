
#ifndef _APIO_FIND
#define _APIO_FIND

#include <apio/function_traits.hpp>
#include <algorithm>

namespace apio {

template <typename T, typename Predicate, typename Consumer>
std::enable_if_t<std::is_same_v<function_return_type<Consumer>, void>>
find_all(T begin, T end, Predicate pred, Consumer consumer) {
    T iter = begin;
    while ((iter = std::find_if(iter, end, pred)) != end)
        consumer(iter), iter++;
}

template <typename T, typename Predicate, typename Consumer,
class = typename std::enable_if<!std::is_same_v<function_return_type<Consumer>, void>>::type>
std::vector<function_return_type<Consumer>>
find_all(T begin, T end, Predicate pred, Consumer consumer) {
    T iter = begin;
    std::vector<function_return_type<Consumer>> data;
    while ((iter = std::find_if(iter, end, pred)) != end)
        data.push_back(consumer(iter)), iter++;
    return data;
}

}

#endif

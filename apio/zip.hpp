
#ifndef _APIO_ZIP
#define _APIO_ZIP

#include "function_traits.hpp"
#include <type_traits>
#include <vector>

namespace apio {

namespace local {
    template <typename Iterator>
    constexpr void advance_all (Iterator & iterator) { ++iterator; }

    template <typename Iterator, typename ... Iterators>
    constexpr void advance_all (Iterator & iterator, Iterators& ... iterators) {
        ++iterator; advance_all(iterators...);
    }
}

template <typename Functor, typename Iterator, typename ... Iterators>
constexpr bool zip_short(Functor callback, Iterator begin, Iterator end, Iterators... iterators) {
    for(; begin != end; ++begin, local::advance_all(iterators...))
        if(!callback(*begin, *(iterators)...))
            return false;
    return true;
}

template <typename Functor, typename Iterator, typename ... Iterators>
std::enable_if_t<std::is_same_v<function_return_type<Functor>, void>>
constexpr zip(Functor callback, Iterator begin, Iterator end, Iterators... iterators) {
    for(; begin != end; ++begin, local::advance_all(iterators...))
        callback(*begin, *(iterators)...);
}

template <typename Functor, typename Iterator, typename ... Iterators,
class = typename std::enable_if<!std::is_same_v<function_return_type<Functor>, void>>::type>
constexpr std::vector<function_return_type<Functor>>
zip(Functor callback, Iterator begin, Iterator end, Iterators... iterators) {
    std::vector<function_return_type<Functor>> zipped;
    for(; begin != end; ++begin, local::advance_all(iterators...))
        zipped.push_back(callback(*begin, *(iterators)...));
    return zipped;
}

}

#endif

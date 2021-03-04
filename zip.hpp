
#ifndef _APIO_ZIP
#define _APIO_ZIP

#include <type_traits>
#include <vector>

template<typename Func>
struct function_traits {
private:
    template<typename Ret, typename... Args>
    static Ret get_return(Ret(*)(Args...));
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...));
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...) const);
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...) const &);
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...) &);
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...) &&);
    template<typename Functor>
    static decltype(get_return(&Functor::operator())) get_return(Functor);
public:
    using return_type = decltype(get_return(std::declval<Func>()));
};

template<typename Func>
using function_return_type = typename function_traits<Func>::return_type;

template <typename Iterator>
constexpr void advance_all (Iterator & iterator) { ++iterator; }

template <typename Iterator, typename ... Iterators>
constexpr void advance_all (Iterator & iterator, Iterators& ... iterators) {
    ++iterator; advance_all(iterators...);
}

template <typename Functor, typename Iterator, typename ... Iterators>
constexpr bool zip_short(Functor callback, Iterator begin, Iterator end, Iterators... iterators) {
    for(; begin != end; ++begin, advance_all(iterators...))
        if(!callback(*begin, *(iterators)...))
            return false;
    return true;
}

template <typename Functor, typename Iterator, typename ... Iterators>
std::enable_if_t<std::is_same_v<function_return_type<Functor>, void>>
constexpr zip(Functor callback, Iterator begin, Iterator end, Iterators... iterators) {
    for(; begin != end; ++begin, advance_all(iterators...))
        callback(*begin, *(iterators)...);
}

template <typename Functor, typename Iterator, typename ... Iterators,
class = typename std::enable_if<!std::is_same_v<function_return_type<Functor>, void>>::type>
constexpr std::vector<function_return_type<Functor>> zip(Functor callback, Iterator begin, Iterator end, Iterators... iterators) {
    std::vector<function_return_type<Functor>> zipped;
    for(; begin != end; ++begin, advance_all(iterators...))
        zipped.push_back(callback(*begin, *(iterators)...));
    return zipped;
}

#endif

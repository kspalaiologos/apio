
#ifndef _APIO_FUNCTION_TRAITS
#define _APIO_FUNCTION_TRAITS

#include <type_traits>
#include <tuple>

namespace apio {

template<typename Func>
struct function_traits {
private:
    template<typename Ret, typename... Args>
    static Ret get_return(Ret(*)(Args...));
    
    template<typename Ret, typename... Args>
    static void get_class(Ret(*)(Args...));
    
    template<typename Ret, typename... Args>
    static std::tuple<Args...> get_args(Ret(*)(Args...));
    
    
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...));
    
    template<typename Ret, typename Class, typename... Args>
    static Class get_class(Ret(Class::*)(Args...));
    
    template<typename Ret, typename Class, typename... Args>
    static std::tuple<Args...> get_args(Ret(Class::*)(Args...));
    
    
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...) const);
    
    template<typename Ret, typename Class, typename... Args>
    static const Class get_class(Ret(Class::*)(Args...) const);
    
    template<typename Ret, typename Class, typename... Args>
    static std::tuple<Args...> get_args(Ret(Class::*)(Args...) const);
    
    
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...) const &);
    
    template<typename Ret, typename Class, typename... Args>
    static const Class &get_class(Ret(Class::*)(Args...) const &);
    
    template<typename Ret, typename Class, typename... Args>
    static std::tuple<Args...> get_args(Ret(Class::*)(Args...) const &);
    
    
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...) &);
    
    template<typename Ret, typename Class, typename... Args>
    static Class &get_class(Ret(Class::*)(Args...) &);
    
    template<typename Ret, typename Class, typename... Args>
    static std::tuple<Args...> get_args(Ret(Class::*)(Args...) &);
    
    
    template<typename Ret, typename Class, typename... Args>
    static Ret get_return(Ret(Class::*)(Args...) &&);
    
    template<typename Ret, typename Class, typename... Args>
    static Class &&get_class(Ret(Class::*)(Args...) &&);
    
    template<typename Ret, typename Class, typename... Args>
    static std::tuple<Args...> get_args(Ret(Class::*)(Args...) &&);
    
    
    template<typename Functor>
    static decltype(get_return(&Functor::operator())) get_return(Functor);
    
    template<typename Functor>
    static decltype(get_class(&Functor::operator())) get_class(Functor);
    
    template<typename Functor>
    static decltype(get_args(&Functor::operator())) get_args(Functor);
    
    
public:
    using return_type = decltype(get_return(std::declval<Func>()));
    using class_type = decltype(get_class(std::declval<Func>()));
    using argument_tuple = decltype(get_args(std::declval<Func>()));
    static constexpr bool is_functor = !std::is_function_v<Func>;
    static constexpr bool is_member = !std::is_same_v<class_type, void>;
    static constexpr bool is_const = std::is_const_v<std::remove_reference_t<class_type>>;
    static constexpr bool is_lvalue_ref = std::is_lvalue_reference_v<class_type>;
    static constexpr bool is_rvalue_ref = std::is_rvalue_reference_v<class_type>;
};


template<typename Func>
using function_return_type = typename function_traits<Func>::return_type;

template<typename Func>
using function_class_type = typename function_traits<Func>::class_type;

template<typename Func>
using function_argument_tuple = typename function_traits<Func>::argument_tuple;

template<std::size_t N, typename Func>
using function_argument_n = std::tuple_element_t<N, function_argument_tuple<Func>>;

template<typename Func>
constexpr bool is_functor = function_traits<Func>::is_functor;

template<typename Func>
constexpr bool is_member_function = function_traits<Func>::is_member;

template<typename Func>
constexpr bool is_const_member_function = function_traits<Func>::is_const;

template<typename Func>
constexpr bool is_lvalue_member_function = function_traits<Func>::is_lvalue_ref;

template<typename Func>
constexpr bool is_rvalue_member_function = function_traits<Func>::is_rvalue_ref;

}

#endif

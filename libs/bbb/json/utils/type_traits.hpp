//
//  bbb/json/type_traits.hpp
//  ofxJsonUtilsTest
//
//  Created by 石井通人 on 2018/07/27.
//

#ifndef type_traits_hpp
#define type_traits_hpp

#include "./common.hpp"

namespace bbb {
    namespace json_utils {
        template <typename ...>
        using void_t = void;
        
        namespace detail {
            template <class AlwaysVoid, template <typename ...> class op, class ... args>
            struct is_detected_impl :std::false_type
            {};
            template <template <typename ...> class op, typename ... args>
            struct is_detected_impl<void_t<op<args ...>>, op, args ...> :std::true_type
            {};
        };
        
        template<template <typename...> class op, class ...args>
        using is_detected = detail::is_detected_impl<void, op, args...>;
    }
};

#endif /* type_traits_hpp */

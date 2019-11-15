//
//  ofxJsonUtilsTypeTraits.h
//
//  Created by ISHII 2bit on 2018/07/29.
//

#ifndef ofxJsonUtilsTypeTraits_h
#define ofxJsonUtilsTypeTraits_h

#include "ofxJsonUtilsCommon.h"

namespace bbb {
    namespace json_utils {
        template <bool b, typename t = void>
        using enable_if_t = typename std::enable_if<b, t>::type;
        
        namespace detail {
            // check toJson
            template <typename checkee>
            using has_toJson_op = typename std::enable_if<std::is_same<ofJson, decltype(std::declval<checkee>().toJson())>::value>::type;
            
            template <typename type>
            using has_toJson = is_detected<has_toJson_op, type>;
            
            // check for loadJson
            template <typename checkee>
            using has_loadJson_op = typename std::enable_if<std::is_same<void, decltype(std::declval<checkee>().loadJson(std::declval<const ofJson &>()))>::value>::type;
            
            template <typename type>
            using has_loadJson = is_detected<has_loadJson_op, type>;
            
            // check has_key
            static bool has_keys(const ofJson &json, const std::vector<std::string> &keys) {
                auto end = json.end();
                bool all = true;
                for(const auto &key : keys) {
                    all &= (json.find(key) != end);
                }
                return all;
            }
        };

#pragma mark glm
#ifdef GLM_VERSION
        template <typename>
        struct is_glm_vec : std::false_type {};
        template <typename>
        struct get_glm_vec_size : std::integral_constant<glm::length_t, 0> {};
        template <typename>
        struct is_glm_mat : std::false_type {};
        
#   if GLM_VERSION < 990
        template <typename T, glm::precision Q>
        struct is_glm_vec<glm::tvec1<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_vec<glm::tvec2<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_vec<glm::tvec3<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_vec<glm::tvec4<T, Q>> : std::true_type {};
        
        template <typename T, glm::precision Q>
        struct get_glm_vec_size<glm::tvec1<T, Q>> : std::integral_constant<glm::length_t, 1> {};
        template <typename T, glm::precision Q>
        struct get_glm_vec_size<glm::tvec2<T, Q>> : std::integral_constant<glm::length_t, 2> {};
        template <typename T, glm::precision Q>
        struct get_glm_vec_size<glm::tvec3<T, Q>> : std::integral_constant<glm::length_t, 3> {};
        template <typename T, glm::precision Q>
        struct get_glm_vec_size<glm::tvec4<T, Q>> : std::integral_constant<glm::length_t, 4> {};
        
        template <typename T, glm::precision Q>
        struct is_glm_mat<glm::tmat2x2<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_mat<glm::tmat2x3<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_mat<glm::tmat2x4<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_mat<glm::tmat3x2<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_mat<glm::tmat3x3<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_mat<glm::tmat3x4<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_mat<glm::tmat4x2<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_mat<glm::tmat4x3<T, Q>> : std::true_type {};
        template <typename T, glm::precision Q>
        struct is_glm_mat<glm::tmat4x4<T, Q>> : std::true_type {};
#   else
        template <glm::length_t N, typename T, glm::qualifier Q>
        struct is_glm_vec<glm::vec<N, T, Q>> : std::true_type {};
        
        template <glm::length_t N, typename T, glm::qualifier Q>
        struct get_glm_vec_size<glm::vec<N, T, Q>> : std::integral_constant<glm::length_t, N> {};
        
        template <glm::length_t M, glm::length_t N, typename T, glm::qualifier Q>
        struct is_glm_mat<glm::mat<M, N, T, Q>> : std::true_type {};
#   endif
        
        template <typename glm_vec_t, std::size_t size>
        constexpr bool is_vec_and_is_size() {
            return is_glm_vec<glm_vec_t>::value && get_glm_vec_size<glm_vec_t>::value == size;
        }
#endif
    };
};

#endif /* ofxJsonUtilsTypeTraits_h */

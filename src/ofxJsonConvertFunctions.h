//
//  ofxJsonConvertFunctions.h
//
//  Created by ISHII 2bit on 2016/05/19.
//
//

#pragma once

#include "../libs/bbb/json/utils/type_traits.hpp"

#include "ofxJsonUtilsCommon.h"
#include "ofxJsonUtilsTypeTraits.h"

namespace bbb {
    namespace json_utils {
        template <typename T>
        static inline auto convert(const T &value)
        -> typename std::enable_if<json_utils::detail::has_toJson<T>::value, ofJson>::type {
            return value.toJson();
        }
        static inline ofJson convert(const ofVec2f &v) {
            return {
                { "x", v.x },
                { "y", v.y }
            };
        }
        
        static inline ofJson convert(const ofVec3f &v) {
            return {
                { "x", v.x },
                { "y", v.y },
                { "z", v.z }
            };
        }
        
        static inline ofJson convert(const ofVec4f &v) {
            return {
                { "x", v.x },
                { "y", v.y },
                { "z", v.z },
                { "w", v.w }
            };
        }
        
        static inline ofJson convert(const ofRectangle &rect) {
            return {
                { "x", rect.x },
                { "y", rect.y },
                { "width", rect.width },
                { "height", rect.height }
            };
        }
        
        static inline ofJson convert(const ofMatrix4x4 &mat) {
            return {
                { "value0", convert(mat._mat[0])},
                { "value1", convert(mat._mat[1])},
                { "value2", convert(mat._mat[2])},
                { "value3", convert(mat._mat[3])},
            };
        }
        
        static inline ofJson convert(const ofQuaternion &v) {
            return {
                { "x", v.x() },
                { "y", v.y() },
                { "z", v.z() },
                { "w", v.w() }
            };
        }

        template <typename PixelType>
        static inline ofJson convert(const ofColor_<PixelType> &c) {
            return {
                { "r", c.r },
                { "g", c.g },
                { "b", c.b },
                { "a", c.a }
            };
        }
        
#pragma mark glm
#ifdef GLM_VERSION
        template <typename glm_vec_t>
        inline auto convert(const glm_vec_t &v)
            -> bbb::json_utils::enable_if_t<is_vec_and_is_size<glm_vec_t, 1>(), ofJson>
        {
            return {
                { "x", v.x },
            };
        }
        template <typename glm_vec_t>
        inline auto convert(const glm_vec_t &v)
            -> bbb::json_utils::enable_if_t<is_vec_and_is_size<glm_vec_t, 2>(), ofJson>
        {
            return {
                { "x", v.x },
                { "y", v.y },
            };
        }
        template <typename glm_vec_t>
        inline auto convert(const glm_vec_t &v)
            -> bbb::json_utils::enable_if_t<is_vec_and_is_size<glm_vec_t, 3>(), ofJson>
        {
            return {
                { "x", v.x },
                { "y", v.y },
                { "z", v.z },
            };
        }
        template <typename glm_vec_t>
        inline auto convert(const glm_vec_t &v)
            -> bbb::json_utils::enable_if_t<is_vec_and_is_size<glm_vec_t, 4>(), ofJson>
        {
            return {
                { "x", v.x },
                { "y", v.y },
                { "z", v.z },
                { "w", v.w },
            };
        }

        template <typename glm_mat_t>
        inline auto convert(const glm_mat_t &v)
            -> bbb::json_utils::enable_if_t<is_glm_mat<glm_mat_t>::value, ofJson>
        {
            ofJson json;
            for(std::size_t i = 0; i < v.length(); ++i) {
                json[ofVAArgsToString("value%d", i)] = convert(v[i]);
            }
            return json;
        }
        
        template <typename T, glm::precision P>
        inline ofJson convert(const glm::tquat<T, P> &v) {
            return {
                { "x", v.x },
                { "y", v.y },
                { "z", v.z },
                { "w", v.w },
            };
        }
#endif // GLM_VERSION
        
        inline ofJson convert(const ofParameter<void> &v) {
            return ofJson();
        }

        template <typename type>
        inline ofJson convert(const ofParameter<type> &v);
        
        inline ofJson convert(const ofParameterGroup &v)
        {
            ofJson j;
#pragma mark so dirty!!
            ofSerialize(j, *const_cast<ofParameterGroup *>(&v));
            return j;
        }
    };
};

namespace ofx {
    namespace JsonUtils = bbb::json_utils;
};

#include "../libs/bbb/json/utils/convert.hpp"

namespace bbb {
    namespace json_utils {
        template <typename type>
        inline ofJson convert(const ofParameter<type> &v) {
            return convert(v.get());
        }
    };
};

#ifdef GLM_VERSION

namespace glm {
    template <typename type>
    auto to_json(ofJson &j, const type &p)
        -> typename std::enable_if<bbb::json_utils::detail::is_convertible<type>::value>::type
    {
        j = bbb::json_utils::convert(p);
    }
};

#endif

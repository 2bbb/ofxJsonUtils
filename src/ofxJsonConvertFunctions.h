//
//  ofxJsonConvertFunctions.h
//
//  Created by ISHII 2bit on 2016/05/19.
//
//

#pragma once

#include "ofMain.h"
#include "ofJson_compatible.h"

namespace bbb {
    namespace json_utils {
        namespace detail {
            template <typename T>
            class has_toJson {
            private:
                template <typename U, U> struct really_has;
                template <typename C>
                static std::true_type Test(really_has<ofJson (C::*)() const, &C::toJson> *);
                template <typename C>
                static std::true_type Test(really_has<ofJson (C::*)(), &C::toJson> *);
                template <typename>
                static std::false_type Test(...);
                
            public:
                static constexpr bool value = decltype(Test<T>(nullptr))::value;
            };
        };
        
        template <typename T>
        static inline auto convert(T &value)
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
        
        template <typename PixelType>
        static inline ofJson convert(const ofColor_<PixelType> &c) {
            return {
                { "r", c.r },
                { "g", c.g },
                { "b", c.b },
                { "a", c.a }
            };
        }
    };
};

namespace ofx {
    namespace JsonUtils = bbb::json_utils;
};

#include "../libs/bbb/json/utils/convert.hpp"

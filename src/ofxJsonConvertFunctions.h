//
//  ofxJsonConvertFunctions.h
//
//  Created by ISHII 2bit on 2016/05/19.
//
//

#pragma once

#include "ofMain.h"
#include "json_compatible.h"
#include "bbb_json_utils/src/json_utils/convert.hpp"

namespace ofx {
    namespace JsonUtils {
        using bbb::json_utils::convert;
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
                static bool const value = decltype(Test<T>(0))::value;
            };
        };
        
        template <typename T>
        static inline auto convert(T &value)
        -> typename std::enable_if<JsonUtils::detail::has_toJson<T>::value, ofJson>::type {
            return value.to_json();
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

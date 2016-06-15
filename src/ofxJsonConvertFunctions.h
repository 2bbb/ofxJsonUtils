//
//  ofxJsonConvertFunctions.h
//
//  Created by ISHII 2bit on 2016/05/19.
//
//

#pragma once

#include "ofMain.h"
#include "json_compatible.h"

namespace ofx {
    namespace JsonUtils {
        namespace detail {
            template <typename T>
            class has_toJson {
            private:
                template <typename U, U> struct really_has;
                template <typename C>
                static std::true_type Test(really_has<ofJson (C::*)() const, &C::toJson> *);
                template <typename C>
                static std::true_type Test(really_has <ofJson (C::*)(), &C::toJson> *);
                template <typename>
                static std::false_type Test(...);
                
            public:
                static bool const value = decltype(Test<T>(0))::value;
            };
        };
        
        const std::string &convert(const std::string &str) {
            return str;
        }
        
        template <typename T>
        auto convert(T value)
        -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
            return value;
        }
        
        template <typename T>
        auto convert(T &value)
        -> typename std::enable_if<detail::has_toJson<T>::value, ofJson>::type {
            return value.toJson();
        }
        
        ofJson convert(const ofVec2f &v) {
            return {
                { "x", v.x },
                { "y", v.y }
            };
        }
        
        ofJson convert(const ofVec3f &v) {
            return {
                { "x", v.x },
                { "y", v.y },
                { "z", v.z }
            };
        }
        
        ofJson convert(const ofVec4f &v) {
            return {
                { "x", v.x },
                { "y", v.y },
                { "z", v.z },
                { "w", v.w }
            };
        }
        
        ofJson convert(const ofRectangle &rect) {
            return {
                { "x", rect.x },
                { "y", rect.y },
                { "width", rect.width },
                { "height", rect.height }
            };
        }
        
        template <typename PixelType>
        ofJson convert(const ofColor_<PixelType> &c) {
            return {
                { "r", c.r },
                { "g", c.g },
                { "b", c.b },
                { "a", c.a }
            };
        }
        
        template <typename T>
        ofJson convert(const std::vector<T> &vec) {
            std::vector<ofJson> json_vec;
            json_vec.resize(vec.size());
            
            for(std::size_t i = 0; i < vec.size(); ++i) {
                json_vec[i] = convert(vec[i]);
            }
            
            return json_vec;
        }
        
        template <typename T>
        ofJson convert(const std::deque<T> &vec) {
            std::vector<ofJson> json_vec;
            json_vec.resize(vec.size());
            
            for(std::size_t i = 0; i < vec.size(); ++i) {
                json_vec[i] = convert(vec[i]);
            }
            
            return json_vec;
        }

        template <typename T, std::size_t size>
        ofJson convert(const std::array<T, size> &arr) {
            std::vector<ofJson> json_vec;
            json_vec.resize(size);
            
            for(std::size_t i = 0; i < size; ++i) {
                json_vec[i] = convert(arr[i]);
            }
            
            return json_vec;
        }

        template <typename T>
        ofJson convert(std::map<std::string, T> &table) {
            std::map<std::string, ofJson> json_map;
            
            for(auto it = table.cbegin(); it != table.cend(); ++it) {
                json_map.emplace(it.first, std::move(convert(it.second)));
            }
            
            return json_map;
        }
    };
};
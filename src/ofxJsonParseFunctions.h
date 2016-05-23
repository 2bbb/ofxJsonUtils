//
//  ofxJsonParseFunctions.h
//
//  Created by ISHII 2bit on 2016/05/19.
//
//

#pragma once

#include "ofMain.h"

namespace ofx {
    namespace JsonUtils {
        namespace detail {
            template <typename T>
            class has_loadJson {
            private:
                template <typename U, U> struct really_has;
                template <typename C>
                static std::true_type Test(really_has<void (C::*)(const ofJson &), &C::loadJson> *);
                template <typename>
                static std::false_type Test(...);
                
            public:
                static bool const value = decltype(Test<T>(0))::value;
            };
        };
        
        inline void parse(const ofJson &json, std::string &value) {
            value = json;
        }
        
        template <typename T>
        auto parse(const ofJson &json, T &value)
        -> typename std::enable_if<std::is_arithmetic<T>::value>::type {
            value = json;
        }
        
        template <typename T>
        auto parse(const ofJson &json, T &value)
        -> typename std::enable_if<detail::has_loadJson<T>::value>::type {
            value.loadJson(json);
        }
        
        void parse(const ofJson &json, ofVec2f &v) {
            v.set(json["x"], json["y"]);
        }
        
        void parse(const ofJson &json, ofVec3f &v) {
            v.set(json["x"], json["y"], json["z"]);
        }
        
        void parse(const ofJson &json, ofVec4f &v) {
            v.set(json["x"], json["y"], json["z"], json["w"]);
        }
        
        void parse(const ofJson &json, ofRectangle &rect) {
            rect.set(json["x"], json["y"], json["width"], json["height"]);
        }
        
        template <typename PixelType>
        void parse(const ofJson &json, ofColor_<PixelType> &c) {
            c.set(json["r"], json["g"], json["b"]);
            if(json.find("a") != json.end()) c.a = json["a"];
        }
        
        template <typename T>
        void parse(const ofJson &json, std::vector<T> &vec) {
            if(!json.is_array()) {
                ofLogWarning("ofxJsonUtils::parse vector") << "json isn't array";
                return;
            }
            vec.clear();
            for(auto j : json) {
                T t;
                parse(j, t);
                vec.push_back(std::move(t));
            }
        }
    };
};
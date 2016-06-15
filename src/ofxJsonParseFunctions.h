//
//  ofxJsonParseFunctions.h
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
            vec.resize(json.size());
            for(std::size_t i = 0; i < json.size(); ++i) {
                parse(json[i], vec[i]);
            }
        }
        
        template <typename T>
        void parse(const ofJson &json, std::deque<T> &vec) {
            if(!json.is_array()) {
                ofLogWarning("ofxJsonUtils::parse deque") << "json isn't array";
                return;
            }
            vec.resize(json.size());
            for(std::size_t i = 0; i < json.size(); ++i) {
                parse(json[i], vec[i]);
            }
        }
        
        template <typename T, std::size_t size>
        void parse(const ofJson &json, std::array<T, size> &arr) {
            if(!json.is_array()) {
                ofLogWarning("ofxJsonUtils::parse array") << "json isn't array";
                return;
            }
            for(std::size_t i = 0; i < json.size(); ++i) {
                if(size <= i) break;
                parse(json[i], arr[i]);
            }
        }

        template <typename T>
        void parse(const ofJson &json, std::map<std::string, T> &table) {
            if(!json.is_object()) {
                ofLogWarning("ofxJsonUtils::parse map") << "json isn't object";
                return;
            }
            table.clear();
            for(ofJson::const_iterator it = json.cbegin(); it != json.cend(); ++it) {
                T t;
                parse(it.value(), t);
                table.emplace(it.key(), std::move(t));
            }
        }
    };
};
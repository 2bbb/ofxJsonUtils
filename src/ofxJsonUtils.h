//
//  ofxJsonUtils.h
//
//  Created by ISHII 2bit on 2016/05/19.
//
//

#pragma once

#include "ofMain.h"
#include "ofxJsonConvertFunctions.h"
#include "ofxJsonParseFunctions.h"

namespace ofx {
    namespace JsonUtils {
        static ofJson parse(const std::string &json_str) {
            return ofJson::parse(json_str);
        }
        
        static ofJson loadFromFile(const std::string &path, bool isInDataDir = true) {
            ofBuffer buffer = ofBufferFromFile(isInDataDir ? ofToDataPath(path, true) : path);
            if(buffer.size() == 0) {
                ofLogWarning("ofxJsonUtils") << path << " not found or empty file";
                return ofJson();
            }
            return ofJson::parse(buffer.getText());
        }
        
        template <typename T>
        ofJson create(const std::string &key, const T &value) {
            ofJson json = ofJson::object();
            json[key] = convert(value);
            return json;
        }

        template <typename T, typename ... Others>
        auto create(const std::string &key, const T &value, const Others & ... others)
        -> typename std::enable_if<2 <= sizeof...(Others) && sizeof...(Others) % 2 == 0, ofJson>::type {
            ofJson json = std::move(create(others ...));
            json[key] = convert(value);
            return json;
        }
        
        template <typename T>
        void load(const ofJson &json, const std::string &key, T &value) {
            parse(json[key], value);
        }

        template <typename T, typename ... Others>
        auto load(const ofJson &json, const std::string &key, T &value, Others && ... others)
        -> typename std::enable_if<2 <= sizeof...(Others) && sizeof...(Others) % 2 == 0, void>::type {
            parse(json[key], value);
            load(json, std::forward<Others>(others) ...);
        }
        
        inline bool ofxJsonToFile(const std::string &path, const ofJson &json, int indent = -1) {
            return ofBufferToFile(path, json.dump(indent));
        }
    };
};

namespace ofxJsonUtils = ofx::JsonUtils;

#define kv(name) #name, name

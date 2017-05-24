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
        static inline ofJson parse(const std::string &json_str) {
            return ofJson::parse(json_str);
        }
        
        static inline ofJson loadFromFile(const std::string &path, bool isInDataDir = true) {
            const ofBuffer buffer = ofBufferFromFile(isInDataDir ? ofToDataPath(path, true) : path);
            if(buffer.size() == 0) {
                ofLogWarning("ofxJsonUtils") << path << " not found or empty file";
                return ofJson();
            }
            return ofJson::parse(buffer.getText());
        }
        
        static inline std::vector<ofJson> loadNDJsonFromFile(const std::string &path, bool isInDataDir = true) {
            ofBuffer buffer = ofBufferFromFile(isInDataDir ? ofToDataPath(path, true) : path);
            std::vector<ofJson> jsons;
            if(buffer.size() == 0) {
                ofLogWarning("ofxJsonUtils") << path << " not found or empty file";
                return jsons;
            }
            for(const auto &line : buffer.getLines()) {
                if(line.empty()) continue;
                jsons.emplace_back(std::move(ofJson::parse(line)));
            }
            return jsons;
        }
        
        template <typename T>
        static inline ofJson create(const std::string &key, const T &value) {
            ofJson json = ofJson::object();
            json[key] = convert(value);
            return json;
        }

        template <typename T, typename ... Others>
        static inline auto create(const std::string &key, const T &value, const Others & ... others)
        -> typename std::enable_if<2 <= sizeof...(Others) && sizeof...(Others) % 2 == 0, ofJson>::type {
            ofJson json = std::move(create(others ...));
            json[key] = convert(value);
            return json;
        }
        
        template <typename T>
        static inline void load(const ofJson &json, const std::string &key, T &value) {
            if(json.find(key) == json.end()) {
                ofLogNotice("ofxJsonUtils::load") << "skip " << key << ". is null";
            } else {
                parse(json[key], value);
            }
        }

        template <typename T, typename ... Others>
        static inline auto load(const ofJson &json, const std::string &key, T &value, Others && ... others)
        -> typename std::enable_if<2 <= sizeof...(Others) && sizeof...(Others) % 2 == 0, void>::type {
            if(json.find(key) == json.end()) {
                ofLogNotice("ofxJsonUtils::load") << "skip " << key << ". is null";
            } else {
                parse(json[key], value);
            }
            load(json, std::forward<Others>(others) ...);
        }

        static inline bool writeToFile(const std::string &path, const ofJson &json, bool isInDataDir = true, int indent = -1) {
            const std::string file_path = isInDataDir ? ofToDataPath(path, true) : path;
            ofBuffer buf;
            buf.append(json.dump(indent));
            return ofBufferToFile(path, buf);
        }
        
        static inline bool writeToNDJsonFile(const std::string &path, const std::vector<ofJson> &jsons, bool isInDataDir = true, int indent = -1) {
            const std::string file_path = isInDataDir ? ofToDataPath(path, true) : path;
            ofBuffer buf;
            for(const auto &json : jsons) {
                buf.append(json.dump(indent));
                buf.append("\n");
            }
            return ofBufferToFile(path, buf);
        }
        
        OF_DEPRECATED_MSG("ofxJsonUtils::ofxJsonToFile() is deprecated, use ofxJsonUtils::writeToFile() instead.", static inline bool ofxJsonToFile(const std::string &path, const ofJson &json, bool isInDataDir = true, int indent = -1))
        {
            return writeToFile(path, json, isInDataDir, indent);
        }
    };
};

#include "ofxJsonify.h"
namespace ofxJsonUtils = ofx::JsonUtils;

#define kv(name) #name, name

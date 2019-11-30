//
//  ofxJsonUtils.h
//
//  Created by ISHII 2bit on 2016/05/19.
//
//

#pragma once

#include "ofxJsonUtilsCommon.h"

#include "ofxJsonConvertFunctions.h"
#include "ofxJsonParseFunctions.h"

#include "../libs/bbb/bbb_json.hpp"
#include "ofJson_compatible.h"
#include "ofxJsonUtilsConvertibleTypes.h"

namespace bbb {
    namespace json_utils {
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
        
        OF_DEPRECATED_MSG("ofxJsonUtils::ofxJsonToFile() is deprecated, use ofxJsonUtils::writeToFile() instead.", static inline bool ofxJsonToFile(const std::string &path, const ofJson &json, bool isInDataDir = true, int indent = -1));
        
        static inline bool ofxJsonToFile(const std::string &path, const ofJson &json, bool isInDataDir, int indent)
        {
            return writeToFile(path, json, isInDataDir, indent);
        }
        
        static inline bool hasKey(const ofJson &json, const std::string &key) {
            return json.find(key) != json.end();
        }
        
        struct key_not_found_exception : public std::exception {
            key_not_found_exception(const std::string &message)
                : message(message) {}
            const std::string message;
            virtual const char* what() const noexcept override {
                return message.c_str();
            }
        };
        
        static inline void validationAssert(const ofJson &json,
                                            const std::string &key)
            throw(key_not_found_exception)
        {
            if(!hasKey(json, key)) {
                throw key_not_found_exception("json: \"" + key + "\" is not exists.");
            }
        }
        
        template <typename ... key_types>
        static inline void validationAssert(const ofJson &json,
                                            const std::string &key,
                                            key_types && ... keys)
        throw(key_not_found_exception)
        {
            validationAssert(json, key);
            validationAssert(json, std::forward<key_types>(keys) ...);
        }
    };
};

#include "ofxJsonify.h"
namespace ofxJsonUtils = bbb::json_utils;

#define kv(name) #name, name

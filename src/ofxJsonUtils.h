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
#include "../libs/bbb/json.hpp"

namespace ofx {
    namespace JsonUtils {
        using bbb::json_utils::parse;
        using bbb::json_utils::parse_ndjson;
        using bbb::json_utils::create;
        using bbb::json_utils::load;
        
        
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
    };
};

#include "ofxJsonify.h"
namespace ofxJsonUtils = ofx::JsonUtils;

#define kv(name) #name, name

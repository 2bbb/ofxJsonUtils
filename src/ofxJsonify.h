//
//  ofxJsonify.h
//  PP_image_gen
//
//  Created by ISHII 2bit on 2016/06/06.
//
//

#pragma once

#ifndef ofxJsonify_h
#define ofxJsonify_h

#include <typeinfo>

#include "ofxJsonUtils.h"

namespace bbb {
    namespace json_utils {
        template <typename Base>
        struct Jsonify {
        public:
            bool loadFromJsonFile(const std::string &path, bool isInDataDir = true) {
                const std::string file_path = isInDataDir ? ofToDataPath(path, true) : path;
                if(!ofFile(file_path).exists()) {
                    ofLogWarning("ofxJsonUtils::loadFromJsonFile") << file_path << " isn't exists";
                    return false;
                }
                parse(json_utils::loadFromFile(path, isInDataDir), static_cast<Base &>(*this));
                return true;
            }
            void loadFromJsonString(const std::string &json_str) {
                parse(json_utils::parse(json_str), static_cast<Base &>(*this));
            }
            
            inline operator ofJson() const { return toJson(); }
            
            virtual ofJson toJson() const {
                ofLogWarning(typeid(Base).name()) << "toJson isn't implemented.";
                return {"warning", "toJson isn't implemented."};
            }
            
            inline std::string toJsonString(int indent = -1) const {
                return toJson().dump(indent);
            }
            
            inline bool writeToJsonFile(const std::string &path, bool isInDataDir = true, int indent = -1) const {
                const std::string file_path = isInDataDir ? ofToDataPath(path, true) : path;
                ofBuffer buf;
                buf.set(toJsonString(indent));
                return ofBufferToFile(file_path, buf);
            }
        };
    }
}

template <typename Base>
using ofxJsonify = bbb::json_utils::Jsonify<Base>;

#endif /* ofxJsonify_h */

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

namespace ofx {
    namespace JsonUtils {
        template <typename Base>
        struct Jsonify {
        public:
            void loadFromJsonFile(const std::string &path, bool isInDataDir = true) {
                parse(JsonUtils::loadFromFile(path, isInDataDir), *dynamic_cast<Base *>(this));
            }
            void loadFromJsonString(const std::string &json_str) {
                parse(JsonUtils::parse(json_str), *dynamic_cast<Base *>(this));
            }
            
            inline operator ofJson() const { return toJson(); }
            
            virtual ofJson toJson() const {
                ofLogWarning(typeid(Base).name()) << "toJson isn't implemented.";
                return {"warning", "toJson isn't implemented."};
            }
            
            inline std::string toJsonString(int indent = -1) const {
                return toJson().dump(indent);
            }
            
            inline bool writeToJsonFile(const std::string &path, int indent = -1) const {
                return ofBufferToFile(path, toJsonString(indent));
            }
        };
    }
}

template <typename Base>
using ofxJsonify = ofx::JsonUtils::Jsonify<Base>;

#endif /* ofxJsonify_h */

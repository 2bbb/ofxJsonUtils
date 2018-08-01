//
//  ofxJsonParseFunctions.h
//
//  Created by ISHII 2bit on 2016/05/19.
//
//

#pragma once

#include "../libs/bbb/json/utils/constants.hpp"
#include "../libs/bbb/json/utils/type_traits.hpp"

#include "ofxJsonUtilsCommon.h"
#include "ofxJsonUtilsTypeTraits.h"

namespace bbb {
    namespace json_utils {
        namespace detail {
        };
        
        template <typename T>
        static inline auto parse(const ofJson &json, T &value)
        -> typename std::enable_if<json_utils::detail::has_loadJson<T>::value>::type {
            value.loadJson(json);
        }
        
        static inline void parse(const ofJson &json, ofVec2f &v) {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x", "y"})) {
                    ofLogVerbose("ofxJsonUtils::parse ofVec2f") << skip_invalid_format;
                    return;
                }
                v.set(json["x"], json["y"]);
            } else if(json.is_array()) {
                if(json.size() < 2) {
                    ofLogVerbose("ofxJsonUtils::parse ofVec2f") << skip_invalid_format;
                    return;
                }
                v.set(json[0], json[1]);
            } else {
                ofLogVerbose("ofxJsonUtils::parse ofVec2f") << skip_json_isnt_object_or_array;
            }
        }
        
        static inline void parse(const ofJson &json, ofVec3f &v) {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x", "y", "z"})) {
                    ofLogVerbose("ofxJsonUtils::parse ofVec3f") << skip_invalid_format;
                    return;
                }
                v.set(json["x"], json["y"], json["z"]);
            } else if(json.is_array()) {
                if(json.size() < 3) {
                    ofLogVerbose("ofxJsonUtils::parse ofVec3f") << skip_invalid_format;
                    return;
                }
                v.set(json[0], json[1], json[2]);
            } else {
                ofLogVerbose("ofxJsonUtils::parse ofVec3f") << skip_json_isnt_object_or_array;
            }
        }
        
        static inline void parse(const ofJson &json, ofVec4f &v) {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x", "y", "z", "w"})) {
                    ofLogVerbose("ofxJsonUtils::parse ofVec4f") << skip_invalid_format;
                    return;
                }
                v.set(json["x"], json["y"], json["z"], json["w"]);
            } else if(json.is_array()) {
                if(json.size() < 4) {
                    ofLogVerbose("ofxJsonUtils::parse ofVec4f") << skip_invalid_format;
                    return;
                }
                v.set(json[0], json[1], json[2], json[3]);
            } else {
                ofLogVerbose("ofxJsonUtils::parse ofVec4f") << skip_json_isnt_object_or_array;
            }
        }
    
        static inline void parse(const ofJson &json, ofRectangle &rect) {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x", "y", "width", "height"})) {
                    ofLogVerbose("ofxJsonUtils::parse ofRectangle") << skip_invalid_format;
                    return;
                }
                rect.set(json["x"], json["y"], json["width"], json["height"]);
            } else if(json.is_array()) {
                if(json.size() < 4) {
                    ofLogVerbose("ofxJsonUtils::parse ofRectangle") << skip_invalid_format;
                    return;
                }
                rect.set(json[0], json[1], json[2], json[3]);
            } else {
                ofLogVerbose("ofxJsonUtils::parse ofRectangle") << skip_json_isnt_object_or_array;
            }
        }
        
        static inline void parse(const ofJson &json, ofMatrix4x4 &mat) {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"value0", "value1", "value2", "value3"})) {
                    ofLogVerbose("ofxJsonUtils::parse ofMatrix4x4") << skip_invalid_format;
                    return;
                }
                parse(json["value0"].get<ofJson::object_t>(), mat._mat[0]);
                parse(json["value1"].get<ofJson::object_t>(), mat._mat[1]);
                parse(json["value2"].get<ofJson::object_t>(), mat._mat[2]);
                parse(json["value3"].get<ofJson::object_t>(), mat._mat[3]);
            } else if(json.is_array()) {
                if(json.size() < 16) {
                    ofLogVerbose("ofxJsonUtils::parse ofMatrix4x4") << skip_invalid_format;
                    return;
                }
                mat.set(json[0], json[1], json[2], json[3], json[4], json[5], json[6], json[7], json[8], json[9], json[10], json[11], json[12], json[13], json[14], json[15]);
            } else {
                ofLogVerbose("ofxJsonUtils::parse ofMatrix4x4") << skip_json_isnt_object_or_array;
            }
        }
        
        static inline void parse(const ofJson &json, ofQuaternion &v) {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x", "y", "z", "w"})) {
                    ofLogVerbose("ofxJsonUtils::parse ofQuaternion") << skip_invalid_format;
                    return;
                }
                v.set(json["x"], json["y"], json["z"], json["w"]);
            } else if(json.is_array()) {
                if(json.size() < 4) {
                    ofLogVerbose("ofxJsonUtils::parse ofQuaternion") << skip_invalid_format;
                    return;
                }
                v.set(json[0], json[1], json[2], json[3]);
            } else {
                ofLogVerbose("ofxJsonUtils::parse ofVec4f") << skip_json_isnt_object_or_array;
            }
        }

        template <typename PixelType>
        static inline void parse(const ofJson &json, ofColor_<PixelType> &c) {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"r", "g", "b"})) {
                    ofLogVerbose("ofxJsonUtils::parse ofColor") << skip_invalid_format;
                    return;
                }
                c.set(json["r"], json["g"], json["b"]);
                if(json.find("a") != json.end()) c.a = json["a"];
            } else if(json.is_array()) {
                if(json.size() < 3) {
                    ofLogVerbose("ofxJsonUtils::parse ofColor") << skip_invalid_format;
                    return;
                }
                c.set(json[0], json[1], json[2]);
                if(3 < json.size()) c.a = json[3];
            } else {
                ofLogVerbose("ofxJsonUtils::parse ofColor") << skip_json_isnt_object_or_array;
            }
        }
        
#pragma mark glm
#ifdef GLM_VERSION
        template <typename glm_vec_t>
        inline auto parse(const ofJson &json, glm_vec_t &v)
            -> bbb::json_utils::enable_if_t<is_vec_and_is_size<glm_vec_t, 1>()>
        {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x"})) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec1") << skip_invalid_format;
                    return;
                }
                v.x = json["x"];
            } else if(json.is_array()) {
                if(json.size() < 1) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec1") << skip_invalid_format;
                    return;
                }
                v.x = json[0];
            } else {
                ofLogVerbose("ofxJsonUtils::parse glm::vec2") << skip_json_isnt_object_or_array;
            }
        }
        template <typename glm_vec_t>
        inline auto parse(const ofJson &json, glm_vec_t &v)
            -> bbb::json_utils::enable_if_t<is_vec_and_is_size<glm_vec_t, 2>()>
        {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x", "y"})) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec2") << skip_invalid_format;
                    return;
                }
                v.x = json["x"];
                v.y = json["y"];
            } else if(json.is_array()) {
                if(json.size() < 2) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec2") << skip_invalid_format;
                    return;
                }
                v.x = json[0];
                v.y = json[1];
            } else {
                ofLogVerbose("ofxJsonUtils::parse glm::vec2") << skip_json_isnt_object_or_array;
            }
        }
        template <typename glm_vec_t>
        inline auto parse(const ofJson &json, glm_vec_t &v)
            -> bbb::json_utils::enable_if_t<is_vec_and_is_size<glm_vec_t, 3>()>
        {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x", "y", "z"})) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec3") << skip_invalid_format;
                    return;
                }
                v.x = json["x"];
                v.y = json["y"];
                v.z = json["z"];
            } else if(json.is_array()) {
                if(json.size() < 3) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec3") << skip_invalid_format;
                    return;
                }
                v.x = json[0];
                v.y = json[1];
                v.z = json[2];
            } else {
                ofLogVerbose("ofxJsonUtils::parse glm::vec3") << skip_json_isnt_object_or_array;
            }
        }
        template <typename glm_vec_t>
        inline auto parse(const ofJson &json, glm_vec_t &v)
            -> bbb::json_utils::enable_if_t<is_vec_and_is_size<glm_vec_t, 4>()>
        {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x", "y", "z", "w"})) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec4") << skip_invalid_format;
                    return;
                }
                v.x = json["x"];
                v.y = json["y"];
                v.z = json["z"];
                v.w = json["w"];
            } else if(json.is_array()) {
                if(json.size() < 3) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec4") << skip_invalid_format;
                    return;
                }
                v.x = json[0];
                v.y = json[1];
                v.z = json[2];
                v.w = json[3];
            } else {
                ofLogVerbose("ofxJsonUtils::parse glm::vec4") << skip_json_isnt_object_or_array;
            }
        }
        
        template <typename glm_mat_t>
        inline auto parse(const ofJson &json, glm_mat_t &mat)
            -> bbb::json_utils::enable_if_t<is_glm_mat<glm_mat_t>::value>
        {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"value0", "value1", "value2", "value3"})) {
                    ofLogVerbose("ofxJsonUtils::parse glm::mat") << skip_invalid_format;
                    return;
                }
                for(std::size_t i = 0; i < mat.length(); ++i) {
                    auto &&j = json[ofVAArgsToString("value%d", i)];
                    parse(j.get<ofJson::object_t>(), mat[i]);
                }
            } else if(json.is_array()) {
                if(json.size() < mat.length() * mat[0].length()) {
                    ofLogVerbose("ofxJsonUtils::parse glm::mat") << skip_invalid_format;
                    return;
                }
                for(std::size_t j = 0; j < mat.length(); ++j) {
                    for(std::size_t i = 0; i < mat[j].length(); ++i) {
                        mat[j][i] = json[j * mat[0].length() + i];
                    }
                }
            } else {
                ofLogVerbose("ofxJsonUtils::parse glm::mat") << skip_json_isnt_object_or_array;
            }
        }
        
        template <typename T, glm::precision P>
        inline void parse(const ofJson &json, glm::tquat<T, P> &v) {
            if(json.is_object()) {
                auto end = json.end();
                if(!json_utils::detail::has_keys(json, {"x", "y", "z", "w"})) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec4") << skip_invalid_format;
                    return;
                }
                v.x = json["x"];
                v.y = json["y"];
                v.z = json["z"];
                v.w = json["w"];
            } else if(json.is_array()) {
                if(json.size() < 3) {
                    ofLogVerbose("ofxJsonUtils::parse glm::vec4") << skip_invalid_format;
                    return;
                }
                v.x = json[0];
                v.y = json[1];
                v.z = json[2];
                v.w = json[3];
            } else {
                ofLogVerbose("ofxJsonUtils::parse glm::vec4") << skip_json_isnt_object_or_array;
            }
        }
#endif // GLM_VERSION
    };
};

namespace ofx {
    namespace JsonUtils = bbb::json_utils;
};

#include "../libs/bbb/json/utils/parse.hpp"

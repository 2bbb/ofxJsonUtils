//
//  bbb/json/utils/utility.hpp
//
//  Created by ISHII 2bit on 2017/05/24.
//
//

#ifndef bbb_json_utils_utility_hpp
#define bbb_json_utils_utility_hpp

#include <sstream>

#include "./common.hpp"

namespace bbb {
    namespace json_utils {
        static inline bbb::json parse(const std::string &json_str) {
            return bbb::json::parse(json_str);
        }
        
        static inline std::vector<bbb::json> parse_ndjson(const std::string &ndjson_str) {
            const char delim('\n');
            std::istringstream is(ndjson_str);
            std::vector<bbb::json> result;
            
            std::string field;
            while(std::getline(is, field, delim)) {
                if(field.empty()) continue;
                result.push_back(bbb::json::parse(field));
            }
            return result;
        }
        
        template <typename type>
        static inline bbb::json create(const std::string &key, const type &value) {
            bbb::json json = bbb::json::object();
            json[key] = convert(value);
            return json;
        }
        
        template <typename type, typename ... others>
        static inline auto create(const std::string &key, const type &value, const others & ... args)
        -> typename std::enable_if<2 <= sizeof...(others) && sizeof...(others) % 2 == 0, bbb::json>::type
        {
            bbb::json json = create(args ...);
            json[key] = convert(value);
            return json;
        }
        
        template <typename type>
        static inline void load(const bbb::json &json, const std::string &key, type &value) {
            if(json.find(key) == json.end()) {
                std::cerr << "[bbb::json_utils::load] " << "skip " << key << ". is null" << std::endl;
            } else {
                parse(json[key], value);
            }
        }
        
        template <typename type, typename ... others>
        static inline auto load(const bbb::json &json, const std::string &key, type &value, others && ... args)
        -> typename std::enable_if<2 <= sizeof...(others) && sizeof...(others) % 2 == 0, void>::type {
            if(json.find(key) == json.end()) {
                std::cerr << "[ofxJsonUtils::load] " << "skip " << key << ". is null" << std::endl;
            } else {
                parse(json[key], value);
            }
            load(json, std::forward<others>(args) ...);
        }

    };
};

#endif /* bbb_json_utils_utility_hpp */

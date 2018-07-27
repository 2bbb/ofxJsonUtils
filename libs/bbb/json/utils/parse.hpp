//
//  bbb/json/parse.hpp
//
//  Created by ISHII 2bit on 2017/05/24.
//
//

#ifndef bbb_json_utils_parse_h
#define bbb_json_utils_parse_h

#include "./common.hpp"

namespace bbb {
    namespace json_utils {
        namespace detail {
            template <typename checkee>
            using has_load_op = typename std::enable_if<std::is_same<void, decltype(std::declval<checkee>().load(std::declval<const ofJson &>()))>::value>::type;
            
            template <typename type>
            using is_json_loadable = is_detected<has_load_op, type>;

            static inline void print_parse_error(const char * const header, const char * const error_str) {
                std::cerr << "[" << header << "] " << error_str << std::endl;
            }
        };
        
        static const inline void parse(const bbb::json &src, bbb::json &dst) {
            dst = src;
        }
        
        static inline void parse(const bbb::json &json, std::string &value) {
            if(!json.is_string()) {
                detail::print_parse_error("bbb::json_utils::parse string",  skip_json_isnt_string);
                return;
            }
            value = json;
        }
        
        static inline void parse(const bbb::json &json, bool &value) {
            if(!json.is_boolean() && !json.is_number()) {
                detail::print_parse_error("bbb::json_utils::parse boolean", skip_json_isnt_boolean);
                return;
            }
            value = json;
        }
        
        template <typename T>
        static inline auto parse(const bbb::json &json, T &value)
        -> typename std::enable_if<std::is_arithmetic<T>::value>::type {
            if(!json.is_number() && !json.is_boolean()) {
                detail::print_parse_error("bbb::json_utils::parse number", skip_json_isnt_number);
                return;
            }
            value = json;
        }
        
        template <typename T>
        static inline auto parse(const bbb::json &json, T &value)
        -> typename std::enable_if<json_utils::detail::is_json_loadable<T>::value>::type {
            value.load(json);
        }
        
        template <typename T>
        static inline void parse(const bbb::json &json, std::shared_ptr<T> &ptr) {
            ptr = std::shared_ptr<T>(new T());
            parse(json, *(ptr.get()));
        }
        
        template <typename type, typename alloc>
        static inline void parse(const bbb::json &json, std::deque<type, alloc> &vec);
        template <typename type, std::size_t size>
        static inline void parse(const bbb::json &json, std::array<type, size> &arr);
        template <typename type, typename comp, typename alloc>
        static inline void parse(const bbb::json &json, std::map<std::string, type, comp, alloc> &table);
        
        template <typename type, typename alloc>
        static inline void parse(const bbb::json &json, std::vector<type, alloc> &vec) {
            if(!json.is_array()) {
                detail::print_parse_error("bbb::json_utils::parse vector", skip_json_isnt_array);
                return;
            }
            vec.resize(json.size());
            for(std::size_t i = 0; i < json.size(); ++i) {
                parse(json[i], vec[i]);
            }
        }
        
        template <typename type, typename alloc>
        static inline void parse(const bbb::json &json, std::deque<type, alloc> &vec) {
            if(!json.is_array()) {
                detail::print_parse_error("bbb::json_utils::parse deque", skip_json_isnt_array);
                return;
            }
            vec.resize(json.size());
            for(std::size_t i = 0; i < json.size(); ++i) {
                parse(json[i], vec[i]);
            }
        }
        
        template <typename type, std::size_t size>
        static inline void parse(const bbb::json &json, std::array<type, size> &arr) {
            if(!json.is_array()) {
                detail::print_parse_error("bbb::json_utils::parse array", skip_json_isnt_array);
                return;
            }
            for(std::size_t i = 0; i < json.size(); ++i) {
                if(size <= i) break;
                parse(json[i], arr[i]);
            }
        }
        
        template <typename type, typename comp, typename alloc>
        static inline void parse(const bbb::json &json, std::map<std::string, type, comp, alloc> &table) {
            if(!json.is_object()) {
                detail::print_parse_error("bbb::json_utils::parse map", skip_json_isnt_object);
                return;
            }
            table.clear();
            for(bbb::json::const_iterator it = json.cbegin(); it != json.cend(); ++it) {
                type t;
                parse(it.value(), t);
                table.emplace(it.key(), std::move(t));
            }
        }
    };
};

#endif /* bbb_json_utils_parse_hpp */

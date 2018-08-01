//
//  bbb/json/convert.hpp
//
//  Created by ISHII 2bit on 2017/05/24.
//
//

#ifndef bbb_json_utils_convert_hpp
#define bbb_json_utils_convert_hpp

#include "./common.hpp"

namespace bbb {
    namespace json_utils {
        namespace detail {
            template <typename checkee>
            using has_to_json_op = typename std::enable_if<std::is_same<bbb::json, decltype(std::declval<checkee>().to_json())>::value>::type;
            
            template <typename type>
            using is_json_encodable = is_detected<has_to_json_op, type>;
        };
        
        static inline const bbb::json &convert(const bbb::json &json) {
            return json;
        }
        
        static inline const std::string &convert(const std::string &str) {
            return str;
        }
        
        template <typename T>
        static inline auto convert(T value)
        -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
            return value;
        }
        
        template <typename type>
        static inline auto convert(const type &value)
        -> typename std::enable_if<json_utils::detail::is_json_encodable<type>::value, bbb::json>::type
        {
            return value.to_json();
        }
        
        template <typename T>
        bbb::json inline convert(const std::shared_ptr<T> &ptr) {
            return ptr ? convert(*(ptr.get())) : bbb::json();
        }
        
        template <typename type, typename alloc>
        static inline bbb::json convert(const std::deque<type, alloc> &vec);
        template <typename type, std::size_t size>
        static inline bbb::json convert(const std::array<type, size> &arr);
        template <typename type, typename comp, typename alloc>
        static inline bbb::json convert(std::map<std::string, type, comp, alloc> &table);
        
        template <typename type, typename alloc>
        static inline bbb::json convert(const std::vector<type, alloc> &vec) {
            std::vector<bbb::json> json_vec;
            json_vec.resize(vec.size());
            
            for(std::size_t i = 0; i < vec.size(); ++i) {
                json_vec[i] = convert(vec[i]);
            }
            
            return json_vec;
        }
        
        template <typename type, typename alloc>
        static inline bbb::json convert(const std::deque<type, alloc> &vec) {
            std::vector<bbb::json> json_vec;
            json_vec.resize(vec.size());
            
            for(std::size_t i = 0; i < vec.size(); ++i) {
                json_vec[i] = convert(vec[i]);
            }
            
            return json_vec;
        }
        
        template <typename type, std::size_t size>
        static inline bbb::json convert(const std::array<type, size> &arr) {
            std::vector<bbb::json> json_vec;
            json_vec.resize(size);
            
            for(std::size_t i = 0; i < size; ++i) {
                json_vec[i] = convert(arr[i]);
            }
            
            return json_vec;
        }
        
        template <typename type, typename comp, typename alloc>
        static inline bbb::json convert(std::map<std::string, type, comp, alloc> &table) {
            std::map<std::string, bbb::json> json_map;
            
            for(auto it = table.cbegin(); it != table.cend(); ++it) {
                json_map.emplace(it->first, std::move(convert(it->second)));
            }
            
            return json_map;
        }
    };
};

#endif /* bbb_json_utils_convert_hpp */

//
//  bbb/json/utils/constants.hpp
//
//  Created by ISHII 2bit on 2017/06/28.
//
//

#ifndef constants_hpp
#define constants_hpp

namespace bbb {
    namespace json_utils {
        static constexpr char const skip_invalid_format[] = "skip: invalid format.";
        static constexpr char const skip_json_isnt_string[] = "skip: json isn't string.";
        static constexpr char const skip_json_isnt_boolean[] = "skip: json isn't boolean.";
        static constexpr char const skip_json_isnt_number[] = "skip: json isn't number.";
        static constexpr char const skip_json_isnt_array[] = "skip: json isn't array.";
        static constexpr char const skip_json_isnt_object[] = "skip: json isn't object.";
        static constexpr char const skip_json_isnt_object_or_array[] = "skip: json isn't object or array.";
    };
};

#endif /* constants_hpp */

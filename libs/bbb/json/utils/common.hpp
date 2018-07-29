//
//  bbb/json/common.hpp
//
//  Created by ISHII 2bit on 2017/05/24.
//
//

#ifndef bbb_json_utils_common_hpp
#define bbb_json_utils_common_hpp

#include <vector>
#include <array>
#include <map>
#include <deque>
#include <memory>
#include <type_traits>

#include "../libs/nlohmann_json/src/json.hpp"
#include "./constants.hpp"
#include "./type_traits.hpp"

namespace bbb {
    using json = nlohmann::json;
};


#endif /* bbb_json_utils_common_hpp */

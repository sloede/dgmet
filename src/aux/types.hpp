#ifndef DGMET_AUX_TYPES_HPP_
#define DGMET_AUX_TYPES_HPP_

#include <cstdint>
#include <string>

namespace dgmet {

/// \name Basic types
///@{
/// General purpose integer type
using Int = int64_t;
/// General purpose integer type, small version
using SInt = int32_t;
/// General purpose index type
using Idx = int64_t;
/// General purpose index type, small version
using SIdx = int32_t;
/// Type for numerical values
using Num = double;
/// String type
using Str = std::string;
///@}

} // namespace dgmet

#endif // ifndef DGMET_AUX_TYPES_HPP_

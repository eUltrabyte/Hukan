#pragma once

#include "../Hukan.hpp"

namespace hk {
    using Float_t = float;
    using Int_t = int32_t;
    using Uint_t = uint32_t;
    using Long_t = long;
    using Long_Long_t = int64_t;
    using Char_t = char;

    using Int8_t = int8_t;
    using Uint8_t = uint8_t;
    using Int16_t = int16_t;
    using Uint16_t = uint16_t;
    using Int32_t = int32_t;
    using Uint32_t = uint32_t;
    using Int64_t = int64_t;
    using Uint64_t = uint64_t;

    extern constexpr Uint_t Bit(Uint_t value) {
        value = 1 << value;
        return value;
    }

    extern constexpr Uint_t Byte(Uint_t value) {
        value = 8 << value;
        return value;
    }
};
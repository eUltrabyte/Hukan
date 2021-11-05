#pragma once

#include "../Hukan.hpp"

namespace hk {
    using Float_t = float;
    using Int_t = int32_t;
    using Uint_t = uint32_t;
    using Long_t = long;
    using Long_Long_t = int64_t;
    using Char_t = char;

    extern constexpr Uint_t Bit(Uint_t value) {
        value = 1 << value;
        return value;
    }

    extern constexpr Uint_t Byte(Uint_t value) {
        value = 8 << value;
        return value;
    }
};
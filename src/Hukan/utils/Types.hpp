#pragma once

#include "../core/Core.hpp"

namespace hk {
    using Char_t = char;
    using Short_t = short;
    using Int_t = int;
    using Uint_t = unsigned int;
    using Float_t = float;
    using Long_t = long;
    using Double_t = double;

    using Int8_t = signed char;
    using Uint8_t = unsigned char;
    using Int16_t = short;
    using Uint16_t = unsigned short;
    using Int32_t = int;
    using Uint32_t = unsigned int;
    using Int64_t = long long;
    using Uint64_t = unsigned long long;

    extern constexpr Uint_t Bit(Uint_t value) {
        value = 1 << value;
        return value;
    }

    extern constexpr Uint_t Byte(Uint_t value) {
        value = 8 << value;
        return value;
    }
};
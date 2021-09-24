#pragma once

#include "../Hukan.hpp"

namespace hk {
    using Float_t = float;
    using Int_t = int32_t;
    using Uint_t = uint32_t;
    using Long_t = long;
    using Long_Long_t = int64_t;
    using Char_t = char;

    struct String_t {
        const Char_t* pData;

        String_t(const Char_t* data) { 
            SetData(data);
        }

        virtual ~String_t() {
            delete this;
        }

        Uint_t GetSize() {
            return sizeof(pData);
        }

        Char_t GetCharAt(const Int_t& position) {
            return pData[position];
        }

        void SetData(const Char_t* data) {
            pData = data;
        }
    };

    extern constexpr Int_t Bit(Int_t value) {
        value = 1 << value;
        return value;
    }

    extern constexpr Uint_t Byte(Uint_t value) {
        value = 8 << value;
        return value;
    }
};
#pragma once

#include "../Hukan.hpp"

namespace hk {
    class HK_API Layer {
    public:
        Layer(VkLayerProperties* pVkLayerProperties = nullptr);
        virtual ~Layer();

        virtual void PrintVkLayerProperties();

        virtual void SetVkLayerProperties(VkLayerProperties* pVkLayerProperties = nullptr);

        HK_NODISCARD virtual const Char_t* GetName() HK_NOEXCEPT;
        HK_NODISCARD virtual const Char_t* GetDescription() HK_NOEXCEPT;
        HK_NODISCARD virtual Uint_t GetSpecificationVersion() HK_NOEXCEPT;
        HK_NODISCARD virtual Uint_t GetImplementationVersion() HK_NOEXCEPT;

        HK_NODISCARD virtual VkLayerProperties* GetVkLayerProperties() HK_NOEXCEPT;

    private:
        VkLayerProperties* mpVkLayerProperties;

    };
};
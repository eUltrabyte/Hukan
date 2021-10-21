#pragma once

#include "../Hukan.hpp"

namespace hk {
    class HK_API Layer {
    public:
        Layer(VkLayerProperties* pVkLayerProperties = nullptr);
        virtual ~Layer();

        virtual void PrintVkLayerProperties();

        virtual void SetVkLayerProperties(VkLayerProperties* pVkLayerProperties = nullptr);

        virtual const Char_t* GetName();
        virtual const Char_t* GetDescription();
        virtual Uint_t GetSpecificationVersion();
        virtual Uint_t GetImplementationVersion();

        virtual VkLayerProperties* GetVkLayerProperties();

    private:
        VkLayerProperties* mpVkLayerProperties;

    };
};
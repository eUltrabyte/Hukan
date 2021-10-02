#pragma once

#include "../Hukan.hpp"

namespace hk {
    class HK_API Layer {
    public:
        Layer(VkLayerProperties* pVkLayerProperties = nullptr);
        virtual ~Layer();

        void PrintVkLayerProperties();

        void SetVkLayerProperties(VkLayerProperties* pVkLayerProperties = nullptr);

        const Char_t* GetName();
        const Char_t* GetDescription();
        Uint_t GetSpecificationVersion();
        Uint_t GetImplementationVersion();

        VkLayerProperties* GetVkLayerProperties();

    private:
        VkLayerProperties* mpVkLayerProperties;
        const Char_t* mName;
        const Char_t* mDescription;
        Uint_t mSpecificationVersion;
        Uint_t mImplementationVersion;

    };
};
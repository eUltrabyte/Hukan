#pragma once

#include "../Hukan.hpp"

namespace hk {
    class HK_API Extension {
    public:
        Extension(VkExtensionProperties* pVkExtensionProperties = nullptr);
        virtual ~Extension();

        void PrintVkExtensionProperties();

        void SetVkExtensionProperties(VkExtensionProperties* pVkExtensionProperties = nullptr);

        const Char_t* GetName();
        Uint_t GetSpecificationVersion();

        VkExtensionProperties* GetVkExtensionProperties();

    private:
        VkExtensionProperties* mpVkExtensionProperties;

    };
};
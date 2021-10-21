#pragma once

#include "../Hukan.hpp"

namespace hk {
    class HK_API Extension {
    public:
        Extension(VkExtensionProperties* pVkExtensionProperties = nullptr);
        virtual ~Extension();

        virtual void PrintVkExtensionProperties();

        virtual void SetVkExtensionProperties(VkExtensionProperties* pVkExtensionProperties = nullptr);

        virtual const Char_t* GetName();
        virtual Uint_t GetSpecificationVersion();

        virtual VkExtensionProperties* GetVkExtensionProperties();

    private:
        VkExtensionProperties* mpVkExtensionProperties;

    };
};
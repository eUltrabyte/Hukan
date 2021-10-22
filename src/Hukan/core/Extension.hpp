#pragma once

#include "../Hukan.hpp"

namespace hk {
    class HK_API Extension {
    public:
        Extension(VkExtensionProperties* pVkExtensionProperties = nullptr);
        virtual ~Extension();

        virtual void PrintVkExtensionProperties();

        virtual void SetVkExtensionProperties(VkExtensionProperties* pVkExtensionProperties = nullptr);

        HK_NODISCARD virtual const Char_t* GetName();
        HK_NODISCARD virtual Uint_t GetSpecificationVersion();

        HK_NODISCARD virtual VkExtensionProperties* GetVkExtensionProperties();

    private:
        VkExtensionProperties* mpVkExtensionProperties;

    };
};
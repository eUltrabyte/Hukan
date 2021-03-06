#pragma once

#include "Core.hpp"

namespace hk {
    class HK_API Extension {
    public:
        Extension(VkExtensionProperties* pVkExtensionProperties = nullptr);
        virtual ~Extension() = default;

        virtual void PrintVkExtensionProperties();

        virtual void SetVkExtensionProperties(VkExtensionProperties* pVkExtensionProperties = nullptr);

        HK_NODISCARD virtual const Char_t* GetName() HK_NOEXCEPT;
        HK_NODISCARD virtual Uint_t GetSpecificationVersion() HK_NOEXCEPT;

        HK_NODISCARD virtual VkExtensionProperties* GetVkExtensionProperties() HK_NOEXCEPT;

    private:
        VkExtensionProperties mVkExtensionProperties;

    };

    namespace Extensions {
        extern void EnumerateExtensions(std::vector<Extension>& extensions) HK_NOEXCEPT;
        extern void EnumerateExtensions(Uint_t& count, std::vector<Extension>& extensions) HK_NOEXCEPT;
    };
};
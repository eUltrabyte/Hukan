#include "Extension.hpp"

namespace hk {
    Extension::Extension(VkExtensionProperties vkExtensionProperties) {
        SetVkExtensionProperties(vkExtensionProperties);
    }

    void Extension::PrintVkExtensionProperties() {
        std::string _format = "instance extension name: " + std::string(GetName());
        Logger::Log(LoggerSeriousness::Info, _format, Terminal::ColorList::Yellow);
        _format = "instance extension specification version: " + std::to_string(GetSpecificationVersion());
        Logger::Log(LoggerSeriousness::Info, _format, Terminal::ColorList::Yellow);
        Logger::Endl();
    }

    void Extension::SetVkExtensionProperties(VkExtensionProperties vkExtensionProperties) {
        mVkExtensionProperties = vkExtensionProperties;
    }

    const Char_t* Extension::GetName() HK_NOEXCEPT {
        return mVkExtensionProperties.extensionName;
    }
    
    Uint_t Extension::GetSpecificationVersion() HK_NOEXCEPT {
        return mVkExtensionProperties.specVersion;
    }

    VkExtensionProperties* Extension::GetVkExtensionProperties() HK_NOEXCEPT {
        return &mVkExtensionProperties;
    }

    namespace Extensions {
        void EnumerateExtensions(std::vector<Extension>& extensions) HK_NOEXCEPT {
            Uint_t count = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
            std::vector<VkExtensionProperties> vkExtensionsProperties(count);
            vkEnumerateInstanceExtensionProperties(nullptr, &count, vkExtensionsProperties.data());
            
            for(auto i = 0; i < vkExtensionsProperties.size(); ++i) {
                extensions.emplace_back(Extension(vkExtensionsProperties.at(i)));
            }

            vkExtensionsProperties.clear();
        }

        void EnumerateExtensions(Uint_t& count, std::vector<Extension>& extensions) HK_NOEXCEPT {
            vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
            std::vector<VkExtensionProperties> vkExtensionsProperties(count);
            vkEnumerateInstanceExtensionProperties(nullptr, &count, vkExtensionsProperties.data());
            
            for(auto i = 0; i < vkExtensionsProperties.size(); ++i) {
                extensions.emplace_back(Extension(vkExtensionsProperties.at(i)));
            }

            vkExtensionsProperties.clear();
        }
    };
};
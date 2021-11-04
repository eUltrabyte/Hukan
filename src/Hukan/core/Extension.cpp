#include "Extension.hpp"

namespace hk {
    Extension::Extension(VkExtensionProperties* pVkExtensionProperties) {
        SetVkExtensionProperties(pVkExtensionProperties);
    }
    
    Extension::~Extension() {
        delete this;
    }

    void Extension::PrintVkExtensionProperties() {
        std::string _format = "instance extension name: " + std::string(GetName());
        Logger::Log(LoggerSeriousness::Info, _format, Terminal::ColorList::Yellow);
        _format = "instance extension specification version: " + std::to_string(GetSpecificationVersion());
        Logger::Log(LoggerSeriousness::Info, _format, Terminal::ColorList::Yellow);
        Logger::Endl();
    }

    void Extension::SetVkExtensionProperties(VkExtensionProperties* pVkExtensionProperties) {
        mpVkExtensionProperties = pVkExtensionProperties;
    }

    const Char_t* Extension::GetName() HK_NOEXCEPT {
        return mpVkExtensionProperties->extensionName;
    }
    
    Uint_t Extension::GetSpecificationVersion() HK_NOEXCEPT {
        return mpVkExtensionProperties->specVersion;
    }

    VkExtensionProperties* Extension::GetVkExtensionProperties() HK_NOEXCEPT {
        return mpVkExtensionProperties;
    }
};
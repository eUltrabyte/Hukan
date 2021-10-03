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
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format, (hk::Int_t)hk::Color::Yellow);
        _format = "instance extension specification version: " + std::to_string(GetSpecificationVersion());
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format, (hk::Int_t)hk::Color::Yellow);
        hk::Logger::Endl();
    }

    void Extension::SetVkExtensionProperties(VkExtensionProperties* pVkExtensionProperties) {
        mpVkExtensionProperties = pVkExtensionProperties;
    }

    const Char_t* Extension::GetName() {
        return mpVkExtensionProperties->extensionName;
    }
    
    Uint_t Extension::GetSpecificationVersion() {
        return mpVkExtensionProperties->specVersion;
    }

    VkExtensionProperties* Extension::GetVkExtensionProperties() {
        return mpVkExtensionProperties;
    }
};
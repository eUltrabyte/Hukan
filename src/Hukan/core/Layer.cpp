#include "Layer.hpp"

namespace hk {
    Layer::Layer(VkLayerProperties* pVkLayerProperties) {
        SetVkLayerProperties(pVkLayerProperties);
    }
    
    Layer::~Layer() {
        delete this;
    }

    void Layer::PrintVkLayerProperties() {
        std::string _format = "instance layer name: " + std::string(GetName());
        Logger::Log(LoggerSeriousness::Info, _format, Terminal::Blue);
        _format = "instance layer description: " + std::string(GetDescription());
        Logger::Log(LoggerSeriousness::Info, _format, Terminal::Blue);
        _format = "instance layer specification version: " + std::to_string(GetSpecificationVersion());
        Logger::Log(LoggerSeriousness::Info, _format, Terminal::Blue);
        _format = "instance layer implementation version: " + std::to_string(GetImplementationVersion());
        Logger::Log(LoggerSeriousness::Info, _format, Terminal::Blue);
        Logger::Endl();
    }

    void Layer::SetVkLayerProperties(VkLayerProperties* pVkLayerProperties) {
        mpVkLayerProperties = pVkLayerProperties;
    }

    const Char_t* Layer::GetName() HK_NOEXCEPT {
        return mpVkLayerProperties->layerName;
    }
    
    const Char_t* Layer::GetDescription() HK_NOEXCEPT {
        return mpVkLayerProperties->description;
    }

    Uint_t Layer::GetSpecificationVersion() HK_NOEXCEPT {
        return mpVkLayerProperties->specVersion;
    }
    
    Uint_t Layer::GetImplementationVersion() HK_NOEXCEPT {
        return mpVkLayerProperties->implementationVersion;
    }

    VkLayerProperties* Layer::GetVkLayerProperties() HK_NOEXCEPT {
        return mpVkLayerProperties;
    }
};
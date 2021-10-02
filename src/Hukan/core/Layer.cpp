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
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format, (hk::Int_t)hk::Color::Blue);
        _format = "instance layer description: " + std::string(GetDescription());
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format, (hk::Int_t)hk::Color::Blue);
        _format = "instance layer specification version: " + std::to_string(GetSpecificationVersion());
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format, (hk::Int_t)hk::Color::Blue);
        _format = "instance layer implementation version: " + std::to_string(GetImplementationVersion());
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format, (hk::Int_t)hk::Color::Blue);
        hk::Logger::Endl();
    }

    void Layer::SetVkLayerProperties(VkLayerProperties* pVkLayerProperties) {
        mpVkLayerProperties = pVkLayerProperties;
    }

    const Char_t* Layer::GetName() {
        return mpVkLayerProperties->layerName;
    }
    
    const Char_t* Layer::GetDescription() {
        return mpVkLayerProperties->description;
    }

    Uint_t Layer::GetSpecificationVersion() {
        return mpVkLayerProperties->specVersion;
    }
    
    Uint_t Layer::GetImplementationVersion() {
        return mpVkLayerProperties->implementationVersion;
    }

    VkLayerProperties* Layer::GetVkLayerProperties() {
        return mpVkLayerProperties;
    }
};
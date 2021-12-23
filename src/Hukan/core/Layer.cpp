#include "Layer.hpp"

namespace hk {
    Layer::Layer(VkLayerProperties vkLayerProperties) {
        SetVkLayerProperties(vkLayerProperties);
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

    void Layer::SetVkLayerProperties(VkLayerProperties vkLayerProperties) {
        mVkLayerProperties = vkLayerProperties;
    }

    const Char_t* Layer::GetName() HK_NOEXCEPT {
        return mVkLayerProperties.layerName;
    }
    
    const Char_t* Layer::GetDescription() HK_NOEXCEPT {
        return mVkLayerProperties.description;
    }

    Uint_t Layer::GetSpecificationVersion() HK_NOEXCEPT {
        return mVkLayerProperties.specVersion;
    }
    
    Uint_t Layer::GetImplementationVersion() HK_NOEXCEPT {
        return mVkLayerProperties.implementationVersion;
    }

    VkLayerProperties* Layer::GetVkLayerProperties() HK_NOEXCEPT {
        return &mVkLayerProperties;
    }

    namespace Layers {
        void EnumerateLayers(std::vector<Layer>& layers) HK_NOEXCEPT {
            Uint_t count = 0;
            vkEnumerateInstanceLayerProperties(&count, nullptr);
            std::vector<VkLayerProperties> vkLayers(count);
            vkEnumerateInstanceLayerProperties(&count, vkLayers.data());

            for(auto i = 0; i < vkLayers.size(); ++i) {
                layers.emplace_back(Layer(vkLayers.at(i)));
            }

            vkLayers.clear();
        }

        void EnumerateLayers(Uint_t& count, std::vector<Layer>& layers) HK_NOEXCEPT {
            vkEnumerateInstanceLayerProperties(&count, nullptr);
            std::vector<VkLayerProperties> vkLayers(count);
            vkEnumerateInstanceLayerProperties(&count, vkLayers.data());

            for(auto i = 0; i < vkLayers.size(); ++i) {
                layers.emplace_back(Layer(vkLayers.at(i)));
            }

            vkLayers.clear();
        }
    };
};
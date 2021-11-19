#include "Messenger.hpp"

namespace hk {
    VKAPI_ATTR VkBool32 VKAPI_CALL HK_API DebugMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::string _format = "validation layer: " + std::string(pCallbackData->pMessage);
        if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            Logger::Log(LoggerSeriousness::Warning, _format);
            Logger::Endl();
        } else if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            Logger::Log(LoggerSeriousness::Error, _format);
            Logger::Endl();
        }
        return VK_FALSE;
    }

    Messenger::Messenger(Instance* pInstance, MessengerCreateInfo* pMessengerCreateInfo) {
        SetInstance(pInstance);
        if(pMessengerCreateInfo != nullptr) {
            SetMessengerCreateInfo(pMessengerCreateInfo);
            CreateVkMessenger();
        }
    }
    
    Messenger::~Messenger() {
        DestroyVkMessenger();
        delete this;
    }

    void Messenger::CreateVkMessenger() {
        auto _func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(*mpInstance->GetVkInstance(), "vkCreateDebugUtilsMessengerEXT");
        if(_func != nullptr) {
            _func(*mpInstance->GetVkInstance(), mpMessengerCreateInfo->GetVkMessengerCreateInfo(), nullptr, &mVkDebugMessenger);
        }
    }
    
    void Messenger::DestroyVkMessenger() {
        auto _func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(*mpInstance->GetVkInstance(), "vkDestroyDebugUtilsMessengerEXT");
        if(_func != nullptr) {
            _func(*mpInstance->GetVkInstance(), mVkDebugMessenger, nullptr);
        }
    }

    void Messenger::SetMessengerCreateInfo(MessengerCreateInfo* pMessengerCreateInfo) {
        mpMessengerCreateInfo = pMessengerCreateInfo;
    }

    void Messenger::SetInstance(Instance* pInstance) {
        mpInstance = pInstance;
    }

    VkDebugUtilsMessengerEXT* Messenger::GetVkMessenger() HK_NOEXCEPT {
        return &mVkDebugMessenger;
    }
};
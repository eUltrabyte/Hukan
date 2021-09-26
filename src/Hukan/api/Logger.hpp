#pragma once

#include "../Hukan.hpp"
#include "Terminal.hpp"

namespace hk {
    enum class LoggerSeriousness {
        None = Bit(0),
        Info = Bit(1),
        Warning = Bit(2),
        Error = Bit(3),
        Critical = Bit(4)
    };

    class HK_API Logger {
    public:
        Logger(const LoggerSeriousness& seriousness, const std::string& format, Int_t color = Bit(0));
        virtual ~Logger();

        static void HK_API Log(const LoggerSeriousness& seriousness, const std::string& format, Int_t color = Bit(0));
        static void HK_API Endl();

        static VkResult CreateMessenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        static void DestroyMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    };

    extern VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
};
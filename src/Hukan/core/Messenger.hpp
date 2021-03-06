#pragma once

#include "Core.hpp"
#include "Instance.hpp"

namespace hk {
    extern VKAPI_ATTR VkBool32 VKAPI_CALL HK_API DebugMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

    struct HK_API MessengerCreateInfo {
    public:
        const void* pNext;
        VkDebugUtilsMessageSeverityFlagsEXT messageSeverity;
        VkDebugUtilsMessageTypeFlagsEXT messageType;
        PFN_vkDebugUtilsMessengerCallbackEXT pfnUserCallback;
        void* pUserData;

    private:
        VkDebugUtilsMessengerCreateInfoEXT mpMessengerCreateInfo;

    public:
        MessengerCreateInfo() {
            pNext = nullptr;
            messageSeverity = (VkDebugUtilsMessageSeverityFlagsEXT)0;
            messageType = (VkDebugUtilsMessageTypeFlagsEXT)0;
            pfnUserCallback = (PFN_vkDebugUtilsMessengerCallbackEXT)0;
            pUserData = nullptr;
        }

        HK_NODISCARD VkDebugUtilsMessengerCreateInfoEXT* GetVkMessengerCreateInfo() HK_NOEXCEPT {
            mpMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            mpMessengerCreateInfo.pNext = pNext;
            mpMessengerCreateInfo.flags = 0;
            mpMessengerCreateInfo.messageSeverity = messageSeverity;
            mpMessengerCreateInfo.messageType = messageType;
            mpMessengerCreateInfo.pfnUserCallback = pfnUserCallback;
            mpMessengerCreateInfo.pUserData = pUserData;
            return &mpMessengerCreateInfo;
        }

    };

    class HK_API Messenger {
    public:
        Messenger(Instance* pInstance = nullptr, MessengerCreateInfo* pMessengerCreateInfo = nullptr);
        virtual ~Messenger();

        virtual void CreateVkMessenger();
        virtual void DestroyVkMessenger();

        virtual void SetMessengerCreateInfo(MessengerCreateInfo* pMessengerCreateInfo = nullptr);
        virtual void SetInstance(Instance* pInstance = nullptr);

        HK_NODISCARD virtual VkDebugUtilsMessengerEXT* GetVkMessenger() HK_NOEXCEPT;

    private:
        Instance* mpInstance;
        MessengerCreateInfo* mpMessengerCreateInfo;
        VkDebugUtilsMessengerEXT mVkDebugMessenger;

    };
};
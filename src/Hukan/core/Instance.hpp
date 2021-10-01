#pragma once

#include "../Hukan.hpp"

namespace hk {
    struct HK_API InstanceCreateInfo {
    public:
        const void* pNext;
        VkApplicationInfo* pAppInfo;
        Uint_t enabledLayersCount;
        const Char_t* const* ppEnabledLayers;
        Uint_t enabledExtensionsCount;
        const Char_t* const* ppEnabledExtensions;

    private:
        VkInstanceCreateInfo pInstanceCreateInfo;

    public:
        InstanceCreateInfo() {
            pNext = nullptr;
            pAppInfo = nullptr;
            enabledLayersCount = 0;
            ppEnabledLayers = nullptr;
            enabledExtensionsCount = 0;
            ppEnabledExtensions = nullptr;
        }

        VkInstanceCreateInfo* GetVkInstanceCreateInfo() {
            pInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            pInstanceCreateInfo.pNext = pNext;
            pInstanceCreateInfo.flags = 0;
            pInstanceCreateInfo.pApplicationInfo = pAppInfo;
            pInstanceCreateInfo.enabledLayerCount = enabledLayersCount;
            pInstanceCreateInfo.ppEnabledLayerNames = ppEnabledLayers;
            pInstanceCreateInfo.enabledExtensionCount = enabledExtensionsCount;
            pInstanceCreateInfo.ppEnabledExtensionNames = ppEnabledExtensions;
            return &pInstanceCreateInfo;
        }
    };

    class HK_API Instance {
    public:
        Instance(InstanceCreateInfo* instanceCreateInfo = nullptr);
        virtual ~Instance();

        void CreateVkInstance();
        void DestroyVkInstance();

        void SetVkInstanceCreateInfo(InstanceCreateInfo* instanceCreateInfo);

        VkInstance* GetVkInstance();

    private:
        InstanceCreateInfo* m_instanceCreateInfo;
        VkInstance m_instance;

    };
};
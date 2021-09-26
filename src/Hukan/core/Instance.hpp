#pragma once

#include "../Hukan.hpp"

namespace hk {
    struct HK_API InstanceCreateInfo {
        VkApplicationInfo* pAppInfo;
        Uint_t enabledLayersCount;
        const Char_t* const* ppEnabledLayers;
        Uint_t enabledExtensionsCount;
        const Char_t* const* ppEnabledExtensions;

        InstanceCreateInfo() {
            pAppInfo = nullptr;
            enabledLayersCount = 0;
            ppEnabledLayers = nullptr;
            enabledExtensionsCount = 0;
            ppEnabledExtensions = nullptr;
        }

        VkInstanceCreateInfo* GetVkInstanceCreateInfo() {
            VkInstanceCreateInfo _instanceCreateInfo;
            _instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            _instanceCreateInfo.pNext = nullptr;
            _instanceCreateInfo.flags = 0;
            _instanceCreateInfo.pApplicationInfo = pAppInfo;
            _instanceCreateInfo.enabledLayerCount = enabledLayersCount;
            _instanceCreateInfo.ppEnabledLayerNames = ppEnabledLayers;
            _instanceCreateInfo.enabledExtensionCount = enabledExtensionsCount;
            _instanceCreateInfo.ppEnabledExtensionNames = ppEnabledExtensions;
            return &_instanceCreateInfo;
        }
    };

    class HK_API Instance {
    public:
        Instance(InstanceCreateInfo* instanceCreateInfo);
        virtual ~Instance();

        void CreateVkInstance();
        void DestroyVkInstance();

        void SetVkInstanceCreateInfo(InstanceCreateInfo* instanceCreateInfo);

        VkInstance* GetVkInstance();

    private:
        InstanceCreateInfo m_instanceCreateInfo;
        VkInstance m_instance;

    };
};
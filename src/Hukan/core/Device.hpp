#pragma once

#include "Core.hpp"
#include "PhysicalDevice.hpp"

namespace hk {
    struct HK_API DeviceCreateInfo {
    public:
        const void* pNext;
        Uint_t queueCreateInfoCount;
        VkDeviceQueueCreateInfo* pQueueCreateInfos;
        Uint_t enabledLayerCount;
        const char** ppEnabledLayerNames;
        Uint_t enabledExtensionCount;
        const char** ppEnabledExtensionNames;
        VkPhysicalDeviceFeatures* pEnabledFeatures;

    private:
        VkDeviceCreateInfo pDeviceCreateInfo;

    public:
        DeviceCreateInfo() {
            pNext = nullptr;
            queueCreateInfoCount = 0;
            pQueueCreateInfos = nullptr;
            enabledLayerCount = 0;
            ppEnabledLayerNames = nullptr;
            enabledExtensionCount = 0;
            ppEnabledExtensionNames = nullptr;
            pEnabledFeatures = nullptr;
        }

        HK_NODISCARD VkDeviceCreateInfo* GetVkDeviceCreateInfo() HK_NOEXCEPT {
            pDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            pDeviceCreateInfo.pNext = pNext;
            pDeviceCreateInfo.flags = 0;
            pDeviceCreateInfo.queueCreateInfoCount = queueCreateInfoCount;
            pDeviceCreateInfo.pQueueCreateInfos = pQueueCreateInfos;
            pDeviceCreateInfo.enabledLayerCount = enabledLayerCount;
            pDeviceCreateInfo.ppEnabledLayerNames = ppEnabledLayerNames;
            pDeviceCreateInfo.enabledExtensionCount = enabledExtensionCount;
            pDeviceCreateInfo.ppEnabledExtensionNames = ppEnabledExtensionNames;
            pDeviceCreateInfo.pEnabledFeatures = pEnabledFeatures;
            return &pDeviceCreateInfo;
        }

    };

    class HK_API Device {
    public:
        Device(PhysicalDevice* pPhysicalDevice, DeviceCreateInfo* pDeviceCreateInfo = nullptr);
        virtual ~Device();

        virtual void Create(PhysicalDevice* pVkPhysicalDevice);
        virtual void Destroy();

        virtual void SetDeviceCreateInfo(DeviceCreateInfo* pDeviceCreateInfo = nullptr);

        HK_NODISCARD virtual VkDevice* GetVkDevice() HK_NOEXCEPT;

    private:
        DeviceCreateInfo* mpDeviceCreateInfo;
        VkDevice mDevice;

    };
};
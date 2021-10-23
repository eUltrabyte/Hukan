#pragma once

#include "../Hukan.hpp"

namespace hk {
    struct HK_API PhysicalDeviceProps {
    public:
        std::string deviceName;
        bool geometryShader;

    private:
        VkPhysicalDeviceProperties pPhysicalDeviceProperties;
        VkPhysicalDeviceFeatures pPhysicalDeviceFeatures;

    public:
        PhysicalDeviceProps() {
            deviceName = "";
            geometryShader = false;
        }

        virtual void GetPhysicalDeviceProps(VkPhysicalDevice* pPhysicalDevice = nullptr) {
            vkGetPhysicalDeviceProperties(*pPhysicalDevice, &pPhysicalDeviceProperties);
            vkGetPhysicalDeviceFeatures(*pPhysicalDevice, &pPhysicalDeviceFeatures);

            deviceName = pPhysicalDeviceProperties.deviceName;
            geometryShader = pPhysicalDeviceFeatures.geometryShader;
        }

        HK_NODISCARD virtual VkPhysicalDeviceProperties* GetVkPhysicalDeviceProperties() {
            return &pPhysicalDeviceProperties;
        }

        HK_NODISCARD virtual VkPhysicalDeviceFeatures* GetVkPhysicalDeviceFeatures() {
            return &pPhysicalDeviceFeatures;
        }
    
    };

    class HK_API PhysicalDevice {
    public:
        PhysicalDevice(VkPhysicalDevice* pPhysicalDevice = nullptr);
        virtual ~PhysicalDevice();

        virtual void PrintPhysicalDeviceProps();

        virtual void SetVkPhysicalDevice(VkPhysicalDevice* pPhysicalDevice = nullptr);

        HK_NODISCARD virtual VkPhysicalDevice* GetVkPhysicalDevice();
        HK_NODISCARD virtual PhysicalDeviceProps* GetPhysicalDeviceProps();

    private:
        VkPhysicalDevice mPhysicalDevice;
        PhysicalDeviceProps mPhysicalDeviceProps;

    };
};
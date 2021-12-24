#pragma once

#include "Core.hpp"
#include "Instance.hpp"

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

        virtual void GetPhysicalDeviceProps(VkPhysicalDevice* pPhysicalDevice = nullptr) HK_NOEXCEPT {
            vkGetPhysicalDeviceProperties(*pPhysicalDevice, &pPhysicalDeviceProperties);
            vkGetPhysicalDeviceFeatures(*pPhysicalDevice, &pPhysicalDeviceFeatures);

            deviceName = pPhysicalDeviceProperties.deviceName;
            geometryShader = pPhysicalDeviceFeatures.geometryShader;
        }

        HK_NODISCARD virtual VkPhysicalDeviceProperties* GetVkPhysicalDeviceProperties() HK_NOEXCEPT {
            return &pPhysicalDeviceProperties;
        }

        HK_NODISCARD virtual VkPhysicalDeviceFeatures* GetVkPhysicalDeviceFeatures() HK_NOEXCEPT {
            return &pPhysicalDeviceFeatures;
        }
    
    };

    class HK_API PhysicalDevice {
    public:
        PhysicalDevice(VkPhysicalDevice* pPhysicalDevice = nullptr);
        virtual ~PhysicalDevice() = default;

        virtual void PrintPhysicalDeviceProps();

        virtual void SetVkPhysicalDevice(VkPhysicalDevice* pPhysicalDevice = nullptr);

        HK_NODISCARD virtual VkPhysicalDevice* GetVkPhysicalDevice() HK_NOEXCEPT;
        HK_NODISCARD virtual PhysicalDeviceProps* GetPhysicalDeviceProps() HK_NOEXCEPT;

    private:
        VkPhysicalDevice mPhysicalDevice;
        PhysicalDeviceProps mPhysicalDeviceProps;

    };

    namespace PhysicalDevices {
        extern void EnumeratePhysicalDevices(Instance& instance, Uint_t& count, std::vector<PhysicalDevice>& physicalDevices);
    };
};
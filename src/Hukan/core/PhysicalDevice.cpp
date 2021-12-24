#include "PhysicalDevice.hpp"

namespace hk {
    PhysicalDevice::PhysicalDevice(VkPhysicalDevice* pPhysicalDevice) {
        SetVkPhysicalDevice(pPhysicalDevice);
        mPhysicalDeviceProps.GetPhysicalDeviceProps(pPhysicalDevice);
    }

    void PhysicalDevice::PrintPhysicalDeviceProps() {
        std::string formatPhysicalDevice = "Device Name: " + std::string(mPhysicalDeviceProps.deviceName);
        Logger::Log(LoggerSeriousness::Info, formatPhysicalDevice);
        formatPhysicalDevice = "Geometry Shader: " + std::to_string(mPhysicalDeviceProps.geometryShader);
        Logger::Log(LoggerSeriousness::Info, formatPhysicalDevice);
        Logger::Endl();
    }

    void PhysicalDevice::SetVkPhysicalDevice(VkPhysicalDevice* pPhysicalDevice) {
        mPhysicalDevice = *pPhysicalDevice;
    }

    VkPhysicalDevice* PhysicalDevice::GetVkPhysicalDevice() HK_NOEXCEPT {
        return &mPhysicalDevice;
    }

    PhysicalDeviceProps* PhysicalDevice::GetPhysicalDeviceProps() HK_NOEXCEPT {
        return &mPhysicalDeviceProps;
    }

    namespace PhysicalDevices {
        void EnumeratePhysicalDevices(Instance& instance, Uint_t& count, std::vector<PhysicalDevice>& physicalDevices) {
            vkEnumeratePhysicalDevices(*instance.GetVkInstance(), &count, nullptr);
            std::vector<VkPhysicalDevice> vkPhysicalDevices(count);
            vkEnumeratePhysicalDevices(*instance.GetVkInstance(), &count, vkPhysicalDevices.data());

            for(auto i = 0; i < vkPhysicalDevices.size(); ++i) {
                physicalDevices.emplace_back(PhysicalDevice(&vkPhysicalDevices.at(i)));
            }

            vkPhysicalDevices.clear();
        }
    };
};
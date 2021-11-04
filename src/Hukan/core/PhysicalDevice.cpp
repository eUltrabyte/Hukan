#include "PhysicalDevice.hpp"

namespace hk {
    PhysicalDevice::PhysicalDevice(VkPhysicalDevice* pPhysicalDevice) {
        SetVkPhysicalDevice(pPhysicalDevice);
        mPhysicalDeviceProps.GetPhysicalDeviceProps(pPhysicalDevice);
    }
    
    PhysicalDevice::~PhysicalDevice() {
        delete this;
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
};
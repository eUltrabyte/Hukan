#include "Device.hpp"

namespace hk {
    Device::Device(PhysicalDevice* pPhysicalDevice, DeviceCreateInfo* pDeviceCreateInfo) {
        SetDeviceCreateInfo(pDeviceCreateInfo);
        Create(pPhysicalDevice);
    }

    Device::~Device() {
        Destroy();
        delete this;
    }

    void Device::Create(PhysicalDevice* pPhysicalDevice) {
        VkResult _result = vkCreateDevice(*pPhysicalDevice->GetVkPhysicalDevice(), mpDeviceCreateInfo->GetVkDeviceCreateInfo(), nullptr, &mDevice);
        HK_ASSERT_VK(_result);
    }
    
    void Device::Destroy() {
        vkDestroyDevice(mDevice, nullptr);
    }

    void Device::SetDeviceCreateInfo(DeviceCreateInfo* pDeviceCreateInfo) {
        mpDeviceCreateInfo = pDeviceCreateInfo;
    }

    VkDevice* Device::GetVkDevice() HK_NOEXCEPT {
        return &mDevice;
    }
};
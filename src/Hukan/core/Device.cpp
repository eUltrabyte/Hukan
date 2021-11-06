#include "Device.hpp"

namespace hk {
    Device::Device(VkPhysicalDevice* pVkPhysicalDevice, DeviceCreateInfo* pDeviceCreateInfo) {
        SetDeviceCreateInfo(pDeviceCreateInfo);
        Create(pVkPhysicalDevice);
    }

    Device::~Device() {
        Destroy();
        delete this;
    }

    void Device::Create(VkPhysicalDevice* pVkPhysicalDevice) {
        VkResult _result = vkCreateDevice(*pVkPhysicalDevice, mpDeviceCreateInfo->GetVkDeviceCreateInfo(), nullptr, &mDevice);
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
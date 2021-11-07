#include "Buffer.hpp"

namespace hk {
    HK_NODISCARD Uint_t HK_API FindMemoryType(VkPhysicalDevice physicalDevice, Uint_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memoryProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

        for(Uint_t i = 0; i < memoryProperties.memoryTypeCount; ++i) {
            if((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }
    }

    Buffer::Buffer(VkPhysicalDevice* pPhysicalDevice, VkDevice* pDevice, BufferCreateInfo* pBufferCreateInfo) {
        SetVkPhysicalDevice(pPhysicalDevice);
        SetVkDevice(pDevice);
        SetBufferCreateInfo(pBufferCreateInfo);
        Create();
    }

    Buffer::~Buffer() {
        Destroy();
        delete this;
    }

    void Buffer::Create() {
        VkResult _result = vkCreateBuffer(*mpDevice, mpBufferCreateInfo->GetVkBufferCreateInfo(), nullptr, &mBuffer);
        HK_ASSERT_VK(_result);

        VkMemoryRequirements _memoryRequirements;
        vkGetBufferMemoryRequirements(*mpDevice, mBuffer, &_memoryRequirements);

        VkMemoryAllocateInfo _memoryAllocateInfo;
        _memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        _memoryAllocateInfo.pNext = nullptr;
        _memoryAllocateInfo.allocationSize = _memoryRequirements.size;
        _memoryAllocateInfo.memoryTypeIndex = hk::FindMemoryType(*mpPhysicalDevice, _memoryRequirements.memoryTypeBits, *mpBufferCreateInfo->GetVkMemoryPropertyFlags());

        _result = vkAllocateMemory(*mpDevice, &_memoryAllocateInfo, nullptr, &mBufferMemory);
        HK_ASSERT_VK(_result);

        Bind();
    }

    void Buffer::Destroy() {
        vkDestroyBuffer(*mpDevice, mBuffer, nullptr);
        vkFreeMemory(*mpDevice, mBufferMemory, nullptr);
    }

    void Buffer::Bind() {
        vkBindBufferMemory(*mpDevice, mBuffer, mBufferMemory, 0);
    }

    void Buffer::SetVkPhysicalDevice(VkPhysicalDevice* pPhysicalDevice) {
        mpPhysicalDevice = pPhysicalDevice;
    }

    void Buffer::SetVkDevice(VkDevice* pDevice) {
        mpDevice = pDevice;
    }

    void Buffer::SetBufferCreateInfo(BufferCreateInfo* pBufferCreateInfo) {
        mpBufferCreateInfo = pBufferCreateInfo;
    }

    VkBuffer* Buffer::GetBuffer() HK_NOEXCEPT {
        return &mBuffer;
    }

    VkDeviceMemory* Buffer::GetBufferMemory() HK_NOEXCEPT {
        return &mBufferMemory;
    }
};
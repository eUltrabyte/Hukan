#pragma once

#include "Core.hpp"
#include "PhysicalDevice.hpp"
#include "Device.hpp"

namespace hk {
    extern HK_NODISCARD Uint_t HK_API FindMemoryType(VkPhysicalDevice physicalDevice, Uint_t typeFilter, VkMemoryPropertyFlags properties);

    struct HK_API BufferCreateInfo {
    public:
        const void* pNext;
        VkDeviceSize size;
        VkBufferUsageFlags usage;
        VkMemoryPropertyFlags properties;

    private:
        VkBufferCreateInfo pVertexBufferCreateInfo;
        VkMemoryPropertyFlags pMemoryPropertyFlags;

    public:
        BufferCreateInfo() {
            pNext = nullptr;
            size = 0;
            usage = 0;
            properties = 0;
        }

        HK_NODISCARD VkBufferCreateInfo* GetVkBufferCreateInfo() {
            pVertexBufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            pVertexBufferCreateInfo.pNext = pNext;
            pVertexBufferCreateInfo.flags = 0;
            pVertexBufferCreateInfo.size = size;
            pVertexBufferCreateInfo.usage = usage;
            pVertexBufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            return &pVertexBufferCreateInfo;
        }

        HK_NODISCARD VkMemoryPropertyFlags* GetVkMemoryPropertyFlags() {
            pMemoryPropertyFlags = properties;
            return &pMemoryPropertyFlags;
        }
        
    };

    class HK_API Buffer {
    public:
        Buffer(PhysicalDevice* pPhysicalDevice, Device* pDevice, BufferCreateInfo* pBufferCreateInfo = nullptr, bool create = true);
        virtual ~Buffer();

        virtual void Create();
        virtual void Destroy();
        virtual void Bind();

        virtual void SetPhysicalDevice(PhysicalDevice* pPhysicalDevice);
        virtual void SetDevice(Device* pDevice);
        virtual void SetBufferCreateInfo(BufferCreateInfo* pBufferCreateInfo = nullptr);

        HK_NODISCARD virtual VkBuffer* GetBuffer() HK_NOEXCEPT;
        HK_NODISCARD virtual VkDeviceMemory* GetBufferMemory() HK_NOEXCEPT;

    private:
        PhysicalDevice* mpPhysicalDevice;
        Device* mpDevice;
        BufferCreateInfo* mpBufferCreateInfo;
        VkBuffer mBuffer;
        VkDeviceMemory mBufferMemory;

    };
};
#include "Instance.hpp"

namespace hk {
    Instance::Instance(InstanceCreateInfo* instanceCreateInfo) {
        SetVkInstanceCreateInfo(instanceCreateInfo);
        CreateVkInstance();
    }
    
    Instance::~Instance() {
        DestroyVkInstance();
        delete this;
    }

    void Instance::CreateVkInstance() {
        VkResult _result = vkCreateInstance(m_instanceCreateInfo.GetVkInstanceCreateInfo(), nullptr, &m_instance);
        HK_ASSERT(_result);
    }
    
    void Instance::DestroyVkInstance() {
        vkDestroyInstance(m_instance, nullptr);
    }

    void Instance::SetVkInstanceCreateInfo(InstanceCreateInfo* instanceCreateInfo) {
        m_instanceCreateInfo = *instanceCreateInfo;
    }

    VkInstance* Instance::GetVkInstance() {
        return &m_instance;
    }
};
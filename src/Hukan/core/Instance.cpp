#include "Instance.hpp"

namespace hk {
    Instance::Instance(InstanceCreateInfo* pInstanceCreateInfo) {
        if(pInstanceCreateInfo != nullptr) {
            SetVkInstanceCreateInfo(pInstanceCreateInfo);
            CreateVkInstance();
        }
    }
    
    Instance::~Instance() {
        DestroyVkInstance();
        delete this;
    }

    void Instance::CreateVkInstance() {
        VkResult _result = vkCreateInstance(mpInstanceCreateInfo->GetVkInstanceCreateInfo(), nullptr, &mInstance);
        HK_ASSERT(_result);
    }
    
    void Instance::DestroyVkInstance() {
        vkDestroyInstance(mInstance, nullptr);
    }

    void Instance::SetVkInstanceCreateInfo(InstanceCreateInfo* pInstanceCreateInfo) {
        mpInstanceCreateInfo = pInstanceCreateInfo;
    }

    VkInstance* Instance::GetVkInstance() HK_NOEXCEPT {
        return &mInstance;
    }
};
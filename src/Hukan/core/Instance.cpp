#include "Instance.hpp"

namespace hk {
    Instance::Instance(InstanceCreateInfo* pInstanceCreateInfo) {
        SetInstanceCreateInfo(pInstanceCreateInfo);
        Create();
    }

    Instance::~Instance() {
        Destroy();
        delete this;
    }

    void Instance::Create() {
        VkResult _result = vkCreateInstance(mpInstanceCreateInfo->GetVkInstanceCreateInfo(), nullptr, &mInstance);
        HK_ASSERT(_result);
    }

    void Instance::Destroy() {
        vkDestroyInstance(mInstance, nullptr);
    }

    void Instance::SetInstanceCreateInfo(InstanceCreateInfo* pInstanceCreateInfo) {
        mpInstanceCreateInfo = pInstanceCreateInfo;
    }

    VkInstance* Instance::GetVkInstance() HK_NOEXCEPT {
        return &mInstance;
    }
};

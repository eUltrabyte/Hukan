#include "Surface.hpp"

namespace hk {
    Surface::Surface() { }
    
    Surface::~Surface() {
        delete this;
    }

    void Surface::Create() { }
    
    void Surface::Destroy() { }

    void Surface::SetVkInstance(VkInstance* pVkInstance) {
        mpVkInstance = pVkInstance;
    }

    void Surface::SetVkSurface(VkSurfaceKHR* pVkSurface) {
        mpVkSurface = pVkSurface;
    }

    VkInstance* Surface::GetVkInstance() HK_NOEXCEPT {
        return mpVkInstance;
    }

    VkSurfaceKHR* Surface::GetVkSurfaceKHR() HK_NOEXCEPT {
        return mpVkSurface;
    }

    void GetSurfaceCapabilities(PhysicalDevice* physicalDevice, Surface* surface, SurfaceCapabilities* capabilities) HK_NOEXCEPT {
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*physicalDevice->GetVkPhysicalDevice(), *surface->GetVkSurfaceKHR(), &surfaceCapabilities);
        capabilities->minImageCount = surfaceCapabilities.minImageCount;
        capabilities->maxImageCount = surfaceCapabilities.maxImageCount;
        capabilities->currentExtent = { surfaceCapabilities.currentExtent.width, surfaceCapabilities.currentExtent.height };
        capabilities->minImageExtent = { surfaceCapabilities.minImageExtent.width, surfaceCapabilities.minImageExtent.height };
        capabilities->maxImageExtent = { surfaceCapabilities.maxImageExtent.width, surfaceCapabilities.maxImageExtent.height };
        capabilities->maxImageArrayLayers = surfaceCapabilities.maxImageArrayLayers;
        capabilities->supportedTransforms = surfaceCapabilities.supportedTransforms;
        capabilities->currentTransform = surfaceCapabilities.currentTransform;
        capabilities->supportedCompositeAlpha = surfaceCapabilities.supportedCompositeAlpha;
        capabilities->supportedUsageFlags = surfaceCapabilities.supportedUsageFlags;
    }
};
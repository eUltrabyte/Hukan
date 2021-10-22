#include <Hukan/Hukan.hpp>

VkResult result;

namespace hk {
    std::vector<Char_t> ReadFile(const std::string& filename) {
        std::ifstream _file(filename, std::ios::binary | std::ios::ate);

        if(_file) {
            size_t _fileSize = (size_t)_file.tellg();
            std::vector<Char_t> _buffer(_fileSize);
            _file.seekg(0);
            _file.read(_buffer.data(), _fileSize);
            _file.close();
            return _buffer;
        } else {
            HK_ASSERT(-1);
            return std::vector<Char_t>(0);
        }
    }
};

int main(int argc, char** argv) {
    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pApplicationName = "Hukan-Example";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 3);
    appInfo.pEngineName = "Hukan";
    appInfo.apiVersion = VK_API_VERSION_1_2;

    hk::Uint_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> vkLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, vkLayers.data());

    std::vector<hk::Layer> layers(layerCount);
    for(int i = 0; i < layers.size(); ++i) {
        layers.at(i).SetVkLayerProperties(&vkLayers.at(i));
        layers.at(i).PrintVkLayerProperties();
    }
    vkLayers.clear();

    hk::Uint_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> vkExtensionsProperties(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, vkExtensionsProperties.data());

    std::vector<hk::Extension> extensions(extensionCount);
    for(int i = 0; i < vkExtensionsProperties.size(); ++i) {
        extensions.at(i).SetVkExtensionProperties(&vkExtensionsProperties.at(i));
        extensions.at(i).PrintVkExtensionProperties();
    }
    vkExtensionsProperties.clear();

    // std::vector<const hk::Char_t*> extensionsNames;
    // for(auto& extension : extensions) {
    //     extensionsNames.push_back(extension.GetName());
    // }

    std::vector<const hk::Char_t*> usedExtensions;

    if(HK_ENABLE_VALIDATION_LAYERS) {
        usedExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
        usedExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
        usedExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    hk::MessengerCreateInfo messengerCreateInfo;
    messengerCreateInfo.pNext = nullptr;
    messengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    messengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    messengerCreateInfo.pfnUserCallback = (PFN_vkDebugUtilsMessengerCallbackEXT)hk::DebugMessengerCallback;
    messengerCreateInfo.pUserData = nullptr;

    hk::InstanceCreateInfo instanceCreateInfo;
    instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)messengerCreateInfo.GetVkMessengerCreateInfo();
    instanceCreateInfo.pAppInfo = &appInfo;
    instanceCreateInfo.enabledLayersCount = hk::g_validationLayers.size();
    instanceCreateInfo.ppEnabledLayers = hk::g_validationLayers.data();
    instanceCreateInfo.enabledExtensionsCount = usedExtensions.size();
    instanceCreateInfo.ppEnabledExtensions = usedExtensions.data();

    hk::Instance instance(&instanceCreateInfo);
    hk::Messenger debugMessenger(instance.GetVkInstance(), &messengerCreateInfo);

    hk::WindowCreateInfo windowCreateInfo;
    windowCreateInfo.title = "Hukan Window Impl Win32";
    windowCreateInfo.width = 1280;
    windowCreateInfo.height = 720;

    hk::WindowImplWin32 window(&windowCreateInfo);

    hk::SurfaceWin32CreateInfo surfaceCreateInfo;
    surfaceCreateInfo.pNext = nullptr;
    surfaceCreateInfo.pHinstance = window.GetHINSTANCE();
    surfaceCreateInfo.pHwnd = window.GetHWND();

    hk::SurfaceWin32 surface(instance.GetVkInstance(), &surfaceCreateInfo);

    hk::Uint_t deviceCount = 0;
    vkEnumeratePhysicalDevices(*instance.GetVkInstance(), &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(*instance.GetVkInstance(), &deviceCount, physicalDevices.data());

    std::vector<VkPhysicalDeviceProperties> physicalDevicesProperties(deviceCount);
    std::vector<VkPhysicalDeviceFeatures> physicalDevicesFeatures(deviceCount);
    for(int i = 0; i < deviceCount; ++i) {
        vkGetPhysicalDeviceProperties(physicalDevices.at(i), &physicalDevicesProperties.at(i));
        vkGetPhysicalDeviceFeatures(physicalDevices.at(i), &physicalDevicesFeatures.at(i));
    }

    for(int i = 0; i < deviceCount; ++i) {
        std::string _format = "Device Name: " + std::string(physicalDevicesProperties.at(i).deviceName);
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
        _format = "Device Geometry Shader: " + std::to_string(physicalDevicesFeatures.at(i).geometryShader);
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
    }

    hk::Logger::Endl();

    VkPhysicalDevice physicalDevice = physicalDevices.at(0);
    physicalDevices.clear();

    physicalDevicesProperties.clear();
    physicalDevicesFeatures.clear();

    hk::Uint_t queueFamiliesCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, nullptr);
    std::vector<VkQueueFamilyProperties> vkFamilyProperties(queueFamiliesCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, vkFamilyProperties.data());

    std::string _format = "Queue Families Count: " + std::to_string(queueFamiliesCount);
    hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
    hk::Logger::Endl();

    for(int i = 0; i < queueFamiliesCount; ++i) {
        std::string _format = "Queue Family Number: " + std::to_string(i);
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
        _format = "VK_QUEUE_GRAPHICS_BIT: " + std::to_string(((vkFamilyProperties.at(i).queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0));
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
        _format = "VK_QUEUE_COMPUTE_BIT: " + std::to_string(((vkFamilyProperties.at(i).queueFlags & VK_QUEUE_COMPUTE_BIT) != 0));
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
        _format = "VK_QUEUE_TRANSFER_BIT: " + std::to_string(((vkFamilyProperties.at(i).queueFlags & VK_QUEUE_TRANSFER_BIT) != 0));
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
        _format = "VK_QUEUE_SPARSE_BINDING_BIT: " + std::to_string(((vkFamilyProperties.at(i).queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0));
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
        _format = "Queue Count: " + std::to_string(vkFamilyProperties.at(i).queueCount);
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
        _format = "Timestamp Valid Bits: " + std::to_string(vkFamilyProperties.at(i).timestampValidBits);
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
        _format = "Minimal Image Timestamp Granularity: " + std::to_string(vkFamilyProperties.at(i).minImageTransferGranularity.width) + ", " + std::to_string(vkFamilyProperties.at(i).minImageTransferGranularity.height) + ", " + std::to_string(vkFamilyProperties.at(i).minImageTransferGranularity.depth);
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
        hk::Logger::Endl();
    }
    vkFamilyProperties.clear();

    float priorities[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    VkDeviceQueueCreateInfo deviceQueueCreateInfo;
    deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.pNext = nullptr;
    deviceQueueCreateInfo.flags = 0;
    deviceQueueCreateInfo.queueFamilyIndex = 0;
    deviceQueueCreateInfo.queueCount = 1;
    deviceQueueCreateInfo.pQueuePriorities = priorities;

    VkPhysicalDeviceFeatures usedFeatures = {  };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkDeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext = nullptr;
    deviceCreateInfo.flags = 0;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    deviceCreateInfo.enabledLayerCount = 0;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;
    deviceCreateInfo.enabledExtensionCount = deviceExtensions.size();
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
    deviceCreateInfo.pEnabledFeatures = &usedFeatures;

    VkDevice device;
    result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
    HK_ASSERT_VK(result);

    VkQueue queue;
    vkGetDeviceQueue(device, 0, 0, &queue);

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, *surface.GetVkSurfaceKHR(), &surfaceCapabilities);
    std::vector<std::string> formatSurfaceCapabilities(10);
    formatSurfaceCapabilities.at(0) = "Surface minImageCount: " + std::to_string(surfaceCapabilities.minImageCount);
    formatSurfaceCapabilities.at(1) = "Surface maxImageCount: " + std::to_string(surfaceCapabilities.maxImageCount);
    formatSurfaceCapabilities.at(2) = "Surface currentExtent: " + std::to_string(surfaceCapabilities.currentExtent.width) + "/" + std::to_string(surfaceCapabilities.currentExtent.height);
    formatSurfaceCapabilities.at(3) = "Surface minImageExtent: " + std::to_string(surfaceCapabilities.minImageExtent.width) + "/" + std::to_string(surfaceCapabilities.minImageExtent.height);
    formatSurfaceCapabilities.at(4) = "Surface maxImageExtent: " + std::to_string(surfaceCapabilities.maxImageExtent.width) + "/" + std::to_string(surfaceCapabilities.maxImageExtent.height);
    formatSurfaceCapabilities.at(5) = "Surface maxImageArrayLayers: " + std::to_string(surfaceCapabilities.maxImageArrayLayers);
    formatSurfaceCapabilities.at(6) = "Surface supportedTransforms: " + std::to_string(surfaceCapabilities.supportedTransforms);
    formatSurfaceCapabilities.at(7) = "Surface currentTransform: " + std::to_string(surfaceCapabilities.currentTransform);
    formatSurfaceCapabilities.at(8) = "Surface supportedCompositeAlpha: " + std::to_string(surfaceCapabilities.supportedCompositeAlpha);
    formatSurfaceCapabilities.at(9) = "Surface supportedUsageFlags: " + std::to_string(surfaceCapabilities.supportedUsageFlags);

    for(int i = 0; i < 10; ++i) {
        hk::Logger::Log(hk::LoggerSeriousness::Info, formatSurfaceCapabilities.at(i));
    }
    hk::Logger::Endl();
    formatSurfaceCapabilities.clear();

    hk::Uint_t formatsCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, *surface.GetVkSurfaceKHR(), &formatsCount, nullptr);
    std::vector<VkSurfaceFormatKHR> surfaceFormats(formatsCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, *surface.GetVkSurfaceKHR(), &formatsCount, surfaceFormats.data());

    std::string formatSurfaceFormats = "Surface Format Count: " + std::to_string(formatsCount);
    hk::Logger::Log(hk::LoggerSeriousness::Info, formatSurfaceFormats);
    for(int i = 0; i < formatsCount; ++i) {
        formatSurfaceFormats = "Surface Format: " + std::to_string(surfaceFormats.at(i).format);
        hk::Logger::Log(hk::LoggerSeriousness::Info, formatSurfaceFormats);
    }
    hk::Logger::Endl();
    surfaceFormats.clear();

    hk::Uint_t presentationModesCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, *surface.GetVkSurfaceKHR(), &presentationModesCount, nullptr);
    std::vector<VkPresentModeKHR> presentationModes(presentationModesCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, *surface.GetVkSurfaceKHR(), &presentationModesCount, presentationModes.data());

    std::string formatPresentationModes = "Surface Present Modes Count: " + std::to_string(presentationModesCount);
    hk::Logger::Log(hk::LoggerSeriousness::Info, formatPresentationModes);
    for(int i = 0; i < presentationModesCount; ++i) {
        formatPresentationModes = "Surface Present Mode: " + std::to_string(presentationModes.at(i));
        hk::Logger::Log(hk::LoggerSeriousness::Info, formatPresentationModes);
    }
    hk::Logger::Endl();
    presentationModes.clear();

    VkBool32 surfaceSupport = false;
    result = vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, 0, *surface.GetVkSurfaceKHR(), &surfaceSupport);
    HK_ASSERT_VK(result);

    if(!surfaceSupport) {
        hk::Logger::Log(hk::LoggerSeriousness::Critical, "Surface Is Not Supported!");
    } else {
        hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface Is Supported");
    }

    VkSwapchainCreateInfoKHR swapchainCreateInfo;
    swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCreateInfo.pNext = nullptr;
    swapchainCreateInfo.flags = 0;
    swapchainCreateInfo.surface = *surface.GetVkSurfaceKHR();
    swapchainCreateInfo.minImageCount = 3; // TODO
    swapchainCreateInfo.imageFormat = VK_FORMAT_B8G8R8A8_SRGB; // TODO
    swapchainCreateInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    swapchainCreateInfo.imageExtent = VkExtent2D { window.GetWindowCreateInfo()->width, window.GetWindowCreateInfo()->height };
    swapchainCreateInfo.imageArrayLayers = 1;
    swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchainCreateInfo.queueFamilyIndexCount = 0;
    swapchainCreateInfo.pQueueFamilyIndices = nullptr;
    swapchainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainCreateInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR; // TODO
    swapchainCreateInfo.clipped = VK_TRUE;
    swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

    VkSwapchainKHR swapchain;
    result = vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &swapchain);
    HK_ASSERT_VK(result);

    hk::Uint_t imagesInSwapchainCount = 0;
    vkGetSwapchainImagesKHR(device, swapchain, &imagesInSwapchainCount, nullptr);
    std::vector<VkImage> swapchainImages(imagesInSwapchainCount);
    vkGetSwapchainImagesKHR(device, swapchain, &imagesInSwapchainCount, swapchainImages.data());

    std::vector<VkImageView> imageViews(imagesInSwapchainCount);
    for(int i = 0; i < imageViews.size(); ++i) {
        VkImageViewCreateInfo imageViewCreateInfo;
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.pNext = nullptr;
        imageViewCreateInfo.flags = 0;
        imageViewCreateInfo.image = swapchainImages.at(i);
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = VK_FORMAT_B8G8R8A8_SRGB;
        imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
        imageViewCreateInfo.subresourceRange.levelCount = 1;
        imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
        imageViewCreateInfo.subresourceRange.layerCount = 1;

        result = vkCreateImageView(device, &imageViewCreateInfo, nullptr, &imageViews.at(i));
        HK_ASSERT_VK(result);
    }

    swapchainImages.clear();

    std::vector<hk::Char_t> vertexShaderCode = hk::ReadFile("vert.spv");

    VkShaderModuleCreateInfo vertexShaderCreateInfo;
    vertexShaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    vertexShaderCreateInfo.pNext = nullptr;
    vertexShaderCreateInfo.flags = 0;
    vertexShaderCreateInfo.codeSize = vertexShaderCode.size();
    vertexShaderCreateInfo.pCode = (hk::Uint_t*)vertexShaderCode.data();

    VkShaderModule vertexShaderModule;
    result = vkCreateShaderModule(device, &vertexShaderCreateInfo, nullptr, &vertexShaderModule);
    HK_ASSERT_VK(result);

    std::vector<hk::Char_t> fragmentShaderCode = hk::ReadFile("frag.spv");

    VkShaderModuleCreateInfo fragmentShaderCreateInfo;
    fragmentShaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    fragmentShaderCreateInfo.pNext = nullptr;
    fragmentShaderCreateInfo.flags = 0;
    fragmentShaderCreateInfo.codeSize = fragmentShaderCode.size();
    fragmentShaderCreateInfo.pCode = (hk::Uint_t*)fragmentShaderCode.data();

    VkShaderModule fragmentShaderModule;
    result = vkCreateShaderModule(device, &fragmentShaderCreateInfo, nullptr, &fragmentShaderModule);
    HK_ASSERT_VK(result);

    window.Update();

    vkDeviceWaitIdle(device);

    for(int i = 0; i < imageViews.size(); ++i) {
        vkDestroyImageView(device, imageViews.at(i), nullptr);
    }
    imageViews.clear();

    vkDestroyShaderModule(device, vertexShaderModule, nullptr);
    vkDestroyShaderModule(device, fragmentShaderModule, nullptr);

    vkDestroySwapchainKHR(device, swapchain, nullptr);

    vkDestroyDevice(device, nullptr);
    surface.Destroy();
    window.Destroy();

    debugMessenger.DestroyVkMessenger();
    instance.DestroyVkInstance();

    std::cin.get();
    return 0;
}
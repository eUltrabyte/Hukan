#include <Hukan/Hukan.hpp>

VkResult result;

namespace hk {
    std::vector<Char_t> HK_API ReadFile(const std::string& filename) {
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

    struct HK_API Vertex {
        Vec3f position;
        Vec4f color;

        static VkVertexInputBindingDescription GetVkVertexInputBindingDescription() {
            VkVertexInputBindingDescription _vertexInputBindingDescription;
            _vertexInputBindingDescription.binding = 0;
            _vertexInputBindingDescription.stride = sizeof(Vertex);
            _vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            return _vertexInputBindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> GetVkVertexInputAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> _vertexInputAttributeDescription;
            _vertexInputAttributeDescription.at(0).binding = 0;
            _vertexInputAttributeDescription.at(0).location = 0;
            _vertexInputAttributeDescription.at(0).format = VK_FORMAT_R32G32B32_SFLOAT;
            _vertexInputAttributeDescription.at(0).offset = offsetof(Vertex, position);
            _vertexInputAttributeDescription.at(1).binding = 0;
            _vertexInputAttributeDescription.at(1).location = 1;
            _vertexInputAttributeDescription.at(1).format = VK_FORMAT_R32G32B32A32_SFLOAT;
            _vertexInputAttributeDescription.at(1).offset = offsetof(Vertex, color);
            return _vertexInputAttributeDescription;
        }
    };

    const std::vector<Vertex> vertices = {
        {{ -1.0f, -1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }},
        {{  1.0f,  1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }},
        {{ -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }},
        {{  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }}
    };

    const std::vector<Uint_t> indices = {
        0, 1, 2, 0, 3, 1
    };

    void HK_API CopyBuffer(VkDevice* pDevice, VkCommandPool* pCommandPool, VkQueue* pQueue, VkBuffer source, VkBuffer destination, VkDeviceSize size) {
        VkCommandBufferAllocateInfo _commandBufferAllocateInfo;
        _commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        _commandBufferAllocateInfo.pNext = nullptr;
        _commandBufferAllocateInfo.commandPool = *pCommandPool;
        _commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        _commandBufferAllocateInfo.commandBufferCount = 1;

        VkCommandBuffer _commandBuffer;
        result = vkAllocateCommandBuffers(*pDevice, &_commandBufferAllocateInfo, &_commandBuffer);
        HK_ASSERT_VK(result);

        VkCommandBufferBeginInfo _commandBufferBeginInfo;
        _commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        _commandBufferBeginInfo.pNext = nullptr;
        _commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        _commandBufferBeginInfo.pInheritanceInfo = nullptr;

        result = vkBeginCommandBuffer(_commandBuffer, &_commandBufferBeginInfo);
        HK_ASSERT_VK(result);

        VkBufferCopy _bufferCopy;
        _bufferCopy.srcOffset = 0;
        _bufferCopy.dstOffset = 0;
        _bufferCopy.size = size;
        vkCmdCopyBuffer(_commandBuffer, source, destination, 1, &_bufferCopy);

        result = vkEndCommandBuffer(_commandBuffer);
        HK_ASSERT_VK(result);

        VkSubmitInfo _submitInfo;
        _submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        _submitInfo.pNext = nullptr;
        _submitInfo.waitSemaphoreCount = 0;
        _submitInfo.pWaitSemaphores = nullptr;
        _submitInfo.pWaitDstStageMask = nullptr;
        _submitInfo.commandBufferCount = 1;
        _submitInfo.pCommandBuffers = &_commandBuffer;
        _submitInfo.signalSemaphoreCount = 0;
        _submitInfo.pSignalSemaphores = nullptr;

        result = vkQueueSubmit(*pQueue, 1, &_submitInfo, VK_NULL_HANDLE);
        HK_ASSERT_VK(result);

        vkQueueWaitIdle(*pQueue);
    }

    struct HK_API UBO {
        Mat4x4f model;
        Mat4x4f view;
        Mat4x4f projection;
    };
};

auto main(int argc, char** argv) -> int {
    hk::Clock clock;
    hk::Int_t fps = 0;

    std::string concurrencyFormat = "Hardware Thread Concurrency: " + std::to_string(hk::Platform::GetHardwareConcurrency());
    hk::Logger::Log(hk::LoggerSeriousness::Info, concurrencyFormat, hk::Terminal::ColorList::Yellow);

    hk::Uint_t instanceVersion = hk::Platform::GetSupportedVulkanVersion();
    std::string versionFormat = "Vulkan Version: " + std::to_string(VK_VERSION_MAJOR(instanceVersion)) + "." + std::to_string(VK_VERSION_MINOR(instanceVersion)) + "." + std::to_string(VK_VERSION_PATCH(instanceVersion));
    hk::Logger::Log(hk::LoggerSeriousness::Info, versionFormat, hk::Terminal::ColorList::Yellow);
    hk::Logger::Endl();

    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pApplicationName = "Hukan-Example";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 3);
    appInfo.pEngineName = "Hukan";
    appInfo.apiVersion = instanceVersion;

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

    std::vector<const hk::Char_t*> usedExtensions;

    if(HK_ENABLE_VALIDATION_LAYERS) {
        usedExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
        #if defined(HUKAN_SYSTEM_WIN32)
            usedExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
        #elif defined(HUKAN_SYSTEM_POSIX)
            usedExtensions.push_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
            usedExtensions.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);
        #endif
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

    #if HK_ENABLE_VALIDATION_LAYERS == false
        instanceCreateInfo.enabledLayersCount = hk::g_validationLayers.size();
        instanceCreateInfo.ppEnabledLayers = hk::g_validationLayers.data();
    #else
        instanceCreateInfo.enabledLayersCount = 0;
        instanceCreateInfo.ppEnabledLayers = nullptr;
    #endif

    instanceCreateInfo.enabledExtensionsCount = usedExtensions.size();
    instanceCreateInfo.ppEnabledExtensions = usedExtensions.data();

    hk::Instance instance(&instanceCreateInfo);
    hk::Messenger debugMessenger(&instance, &messengerCreateInfo);

    hk::WindowCreateInfo windowCreateInfo;
    windowCreateInfo.width = 1280;
    windowCreateInfo.height = 720;

    #if defined(HUKAN_SYSTEM_WIN32)
        windowCreateInfo.title = "Hukan Window Impl Win32";

        hk::WindowImplWin32 window(&windowCreateInfo);

        hk::SurfaceWin32CreateInfo surfaceWin32CreateInfo;
        surfaceWin32CreateInfo.pNext = nullptr;
        surfaceWin32CreateInfo.pHinstance = window.GetHINSTANCE();
        surfaceWin32CreateInfo.pHwnd = window.GetHWND();

        hk::SurfaceWin32 surface(instance.GetVkInstance(), &surfaceWin32CreateInfo);
    #elif defined(HUKAN_SYSTEM_POSIX)
        windowCreateInfo.title = "Hukan Window Impl Posix";

        hk::WindowImplPosix window(&windowCreateInfo);

        hk::SurfacePosixCreateInfo surfacePosixCreateInfo;
        surfacePosixCreateInfo.pNext = nullptr;
        surfacePosixCreateInfo.pDisplay = window.GetDisplay();
        surfacePosixCreateInfo.pWindow = window.GetWindow();

        hk::SurfacePosix surface(instance.GetVkInstance(), &surfacePosixCreateInfo);
    #endif

    hk::Uint_t physicalDevicesCount = 0;
    vkEnumeratePhysicalDevices(*instance.GetVkInstance(), &physicalDevicesCount, nullptr);
    std::vector<VkPhysicalDevice> physicalDevices(physicalDevicesCount);
    vkEnumeratePhysicalDevices(*instance.GetVkInstance(), &physicalDevicesCount, physicalDevices.data());

    hk::PhysicalDevice physicalDevice(&physicalDevices.at(0));
    physicalDevice.PrintPhysicalDeviceProps();
    physicalDevices.clear();

    hk::Float_t priorities[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    VkDeviceQueueCreateInfo deviceQueueCreateInfo;
    deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.pNext = nullptr;
    deviceQueueCreateInfo.flags = 0;
    deviceQueueCreateInfo.queueFamilyIndex = 0;
    deviceQueueCreateInfo.queueCount = 1;
    deviceQueueCreateInfo.pQueuePriorities = priorities;

    VkPhysicalDeviceFeatures usedFeatures = {  };

    const hk::Char_t* deviceExtensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    hk::DeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.pNext = nullptr;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    deviceCreateInfo.enabledLayerCount = 0;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;
    deviceCreateInfo.enabledExtensionCount = 1;
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;
    deviceCreateInfo.pEnabledFeatures = &usedFeatures;

    hk::Device device(&physicalDevice, &deviceCreateInfo);

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*physicalDevice.GetVkPhysicalDevice(), *surface.GetVkSurfaceKHR(), &surfaceCapabilities);
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
    vkGetPhysicalDeviceSurfaceFormatsKHR(*physicalDevice.GetVkPhysicalDevice(), *surface.GetVkSurfaceKHR(), &formatsCount, nullptr);
    std::vector<VkSurfaceFormatKHR> surfaceFormats(formatsCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(*physicalDevice.GetVkPhysicalDevice(), *surface.GetVkSurfaceKHR(), &formatsCount, surfaceFormats.data());

    std::string formatSurfaceFormats = "Surface Format Count: " + std::to_string(formatsCount);
    hk::Logger::Log(hk::LoggerSeriousness::Info, formatSurfaceFormats);
    for(int i = 0; i < formatsCount; ++i) {
        formatSurfaceFormats = "Surface Format: " + std::to_string(surfaceFormats.at(i).format);
        hk::Logger::Log(hk::LoggerSeriousness::Info, formatSurfaceFormats);
    }
    hk::Logger::Endl();
    surfaceFormats.clear();

    hk::Uint_t presentationModesCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(*physicalDevice.GetVkPhysicalDevice(), *surface.GetVkSurfaceKHR(), &presentationModesCount, nullptr);
    std::vector<VkPresentModeKHR> presentationModes(presentationModesCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(*physicalDevice.GetVkPhysicalDevice(), *surface.GetVkSurfaceKHR(), &presentationModesCount, presentationModes.data());

    std::string formatPresentationModes = "Surface Present Modes Count: " + std::to_string(presentationModesCount);
    hk::Logger::Log(hk::LoggerSeriousness::Info, formatPresentationModes);
    for(int i = 0; i < presentationModesCount; ++i) {
        formatPresentationModes = "Surface Present Mode: " + std::to_string(presentationModes.at(i));
        hk::Logger::Log(hk::LoggerSeriousness::Info, formatPresentationModes);
    }
    hk::Logger::Endl();
    presentationModes.clear();

    hk::Uint_t queueFamiliesCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice.GetVkPhysicalDevice(), &queueFamiliesCount, nullptr);
    std::vector<VkQueueFamilyProperties> vkFamilyProperties(queueFamiliesCount);
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice.GetVkPhysicalDevice(), &queueFamiliesCount, vkFamilyProperties.data());

    std::string _format = "Queue Families Count: " + std::to_string(queueFamiliesCount);
    hk::Logger::Log(hk::LoggerSeriousness::Info, _format);
    hk::Logger::Endl();

    hk::Int_t graphicsQueueCount = 0;
    hk::Int_t presentQueueCount = 0;
    for(int i = 0; i < queueFamiliesCount; ++i) {
        if(vkFamilyProperties.at(i).queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            graphicsQueueCount = i;
        }

        VkBool32 surfaceSupport = false;
        result = vkGetPhysicalDeviceSurfaceSupportKHR(*physicalDevice.GetVkPhysicalDevice(), i, *surface.GetVkSurfaceKHR(), &surfaceSupport);
        HK_ASSERT_VK(result);

        if(surfaceSupport) {
            presentQueueCount = i;
        }

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

    if(!presentQueueCount) {
        hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface Is Supported");
    } else {
        hk::Logger::Log(hk::LoggerSeriousness::Critical, "Surface Is Not Supported!");
    }
    hk::Logger::Endl();

    VkQueue graphicsQueue;
    vkGetDeviceQueue(*device.GetVkDevice(), graphicsQueueCount, 0, &graphicsQueue);
    VkQueue presentQueue;
    vkGetDeviceQueue(*device.GetVkDevice(), presentQueueCount, 0, &presentQueue);

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
    swapchainCreateInfo.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR; // TODO // VK_PRESENT_MODE_FIFO_KHR // VK_PRESENT_MODE_IMMEDIATE_KHR
    swapchainCreateInfo.clipped = VK_TRUE;
    swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

    VkSwapchainKHR swapchain;
    result = vkCreateSwapchainKHR(*device.GetVkDevice(), &swapchainCreateInfo, nullptr, &swapchain);
    HK_ASSERT_VK(result);

    hk::Uint_t imagesInSwapchainCount = 0;
    vkGetSwapchainImagesKHR(*device.GetVkDevice(), swapchain, &imagesInSwapchainCount, nullptr);
    std::vector<VkImage> swapchainImages(imagesInSwapchainCount);
    vkGetSwapchainImagesKHR(*device.GetVkDevice(), swapchain, &imagesInSwapchainCount, swapchainImages.data());

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

        result = vkCreateImageView(*device.GetVkDevice(), &imageViewCreateInfo, nullptr, &imageViews.at(i));
        HK_ASSERT_VK(result);
    }

    swapchainImages.clear();

    VkDescriptorSetLayoutBinding descriptorSetLayoutBinding;
    descriptorSetLayoutBinding.binding = 0;
    descriptorSetLayoutBinding.descriptorCount = 1;
    descriptorSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorSetLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    descriptorSetLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo;
    descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetLayoutCreateInfo.pNext = nullptr;
    descriptorSetLayoutCreateInfo.flags = 0;
    descriptorSetLayoutCreateInfo.bindingCount = 1;
    descriptorSetLayoutCreateInfo.pBindings = &descriptorSetLayoutBinding;

    VkDescriptorSetLayout descriptorSetLayout;
    result = vkCreateDescriptorSetLayout(*device.GetVkDevice(), &descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayout);
    HK_ASSERT_VK(result);

    std::vector<hk::Char_t> vertexShaderCode = hk::ReadFile("shader.vert.spv");

    VkShaderModuleCreateInfo vertexShaderCreateInfo;
    vertexShaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    vertexShaderCreateInfo.pNext = nullptr;
    vertexShaderCreateInfo.flags = 0;
    vertexShaderCreateInfo.codeSize = vertexShaderCode.size();
    vertexShaderCreateInfo.pCode = (hk::Uint_t*)vertexShaderCode.data();

    VkShaderModule vertexShaderModule;
    result = vkCreateShaderModule(*device.GetVkDevice(), &vertexShaderCreateInfo, nullptr, &vertexShaderModule);
    HK_ASSERT_VK(result);

    std::vector<hk::Char_t> fragmentShaderCode = hk::ReadFile("shader.frag.spv");

    VkShaderModuleCreateInfo fragmentShaderCreateInfo;
    fragmentShaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    fragmentShaderCreateInfo.pNext = nullptr;
    fragmentShaderCreateInfo.flags = 0;
    fragmentShaderCreateInfo.codeSize = fragmentShaderCode.size();
    fragmentShaderCreateInfo.pCode = (hk::Uint_t*)fragmentShaderCode.data();

    VkShaderModule fragmentShaderModule;
    result = vkCreateShaderModule(*device.GetVkDevice(), &fragmentShaderCreateInfo, nullptr, &fragmentShaderModule);
    HK_ASSERT_VK(result);

    VkPipelineShaderStageCreateInfo vertexShaderStageCreateInfo;
    vertexShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertexShaderStageCreateInfo.pNext = nullptr;
    vertexShaderStageCreateInfo.flags = 0;
    vertexShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertexShaderStageCreateInfo.module = vertexShaderModule;
    vertexShaderStageCreateInfo.pName = "main";
    vertexShaderStageCreateInfo.pSpecializationInfo = nullptr;

    VkPipelineShaderStageCreateInfo fragmentShaderStageCreateInfo;
    fragmentShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragmentShaderStageCreateInfo.pNext = nullptr;
    fragmentShaderStageCreateInfo.flags = 0;
    fragmentShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragmentShaderStageCreateInfo.module = fragmentShaderModule;
    fragmentShaderStageCreateInfo.pName = "main";
    fragmentShaderStageCreateInfo.pSpecializationInfo = nullptr;

    VkPipelineShaderStageCreateInfo shaderStagesCreateInfos[2] = { vertexShaderStageCreateInfo, fragmentShaderStageCreateInfo };

    auto bindingDescription = hk::Vertex::GetVkVertexInputBindingDescription();
    auto attributeDescriptions = hk::Vertex::GetVkVertexInputAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo;
    vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateCreateInfo.pNext = nullptr;
    vertexInputStateCreateInfo.flags = 0;
    vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
    vertexInputStateCreateInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputStateCreateInfo.vertexAttributeDescriptionCount = attributeDescriptions.size();
    vertexInputStateCreateInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo;
    inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateCreateInfo.pNext = nullptr;
    inputAssemblyStateCreateInfo.flags = 0;
    inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport;
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = window.GetWindowCreateInfo()->width;
    viewport.height = window.GetWindowCreateInfo()->height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor;
    scissor.offset = { 0, 0 };
    scissor.extent = { window.GetWindowCreateInfo()->width, window.GetWindowCreateInfo()->height };

    VkPipelineViewportStateCreateInfo viewportStateCreateInfo;
    viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateCreateInfo.pNext = nullptr;
    viewportStateCreateInfo.flags = 0;
    viewportStateCreateInfo.viewportCount = 1;
    viewportStateCreateInfo.pViewports = &viewport;
    viewportStateCreateInfo.scissorCount = 1;
    viewportStateCreateInfo.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo;
    rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateCreateInfo.pNext = nullptr;
    rasterizationStateCreateInfo.flags = 0;
    rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
    rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
    rasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
    rasterizationStateCreateInfo.depthBiasClamp = 0.0f;
    rasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f;
    rasterizationStateCreateInfo.lineWidth = 1.0f;

    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo;
    multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCreateInfo.pNext = nullptr;
    multisampleStateCreateInfo.flags = 0;
    multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
    multisampleStateCreateInfo.minSampleShading = 1.0f;
    multisampleStateCreateInfo.pSampleMask = nullptr;
    multisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
    multisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;

    VkPipelineColorBlendAttachmentState colorBlendAttachmentState;
    colorBlendAttachmentState.blendEnable = VK_TRUE;
    colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo;
    colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlendStateCreateInfo.pNext = nullptr;
    colorBlendStateCreateInfo.flags = 0;
    colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
    colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_NO_OP;
    colorBlendStateCreateInfo.attachmentCount = 1;
    colorBlendStateCreateInfo.pAttachments = &colorBlendAttachmentState;
    colorBlendStateCreateInfo.blendConstants[0] = 0.0f;
    colorBlendStateCreateInfo.blendConstants[1] = 0.0f;
    colorBlendStateCreateInfo.blendConstants[2] = 0.0f;
    colorBlendStateCreateInfo.blendConstants[3] = 0.0f;

    VkPipelineLayoutCreateInfo layoutCreateInfo;
    layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    layoutCreateInfo.pNext = nullptr;
    layoutCreateInfo.flags = 0;
    layoutCreateInfo.setLayoutCount = 1;
    layoutCreateInfo.pSetLayouts = &descriptorSetLayout;
    layoutCreateInfo.pushConstantRangeCount = 0;
    layoutCreateInfo.pPushConstantRanges = nullptr;

    VkPipelineLayout layout;
    result = vkCreatePipelineLayout(*device.GetVkDevice(), &layoutCreateInfo, nullptr, &layout);
    HK_ASSERT_VK(result);

    VkAttachmentDescription attachmentDescription;
    attachmentDescription.flags = 0;
    attachmentDescription.format = VK_FORMAT_B8G8R8A8_SRGB;
    attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference attachmentReference;
    attachmentReference.attachment = 0;
    attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpassDescription;
    subpassDescription.flags = 0;
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.inputAttachmentCount = 0;
    subpassDescription.pInputAttachments = nullptr;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &attachmentReference;
    subpassDescription.pResolveAttachments = nullptr;
    subpassDescription.pDepthStencilAttachment = nullptr;
    subpassDescription.preserveAttachmentCount = 0;
    subpassDescription.pPreserveAttachments = nullptr;

    VkSubpassDependency subpassDependency;
    subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependency.dstSubpass = 0;
    subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependency.srcAccessMask = 0;
    subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependency.dependencyFlags = 0;

    VkRenderPassCreateInfo renderPassCreateInfo;
    renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.pNext = nullptr;
    renderPassCreateInfo.flags = 0;
    renderPassCreateInfo.attachmentCount = 1;
    renderPassCreateInfo.pAttachments = &attachmentDescription;
    renderPassCreateInfo.subpassCount = 1;
    renderPassCreateInfo.pSubpasses = &subpassDescription;
    renderPassCreateInfo.dependencyCount = 1;
    renderPassCreateInfo.pDependencies = &subpassDependency;

    VkRenderPass renderPass;
    result = vkCreateRenderPass(*device.GetVkDevice(), &renderPassCreateInfo, nullptr, &renderPass);
    HK_ASSERT_VK(result);

    VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo;
    graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    graphicsPipelineCreateInfo.pNext = nullptr;
    graphicsPipelineCreateInfo.flags = 0;
    graphicsPipelineCreateInfo.stageCount = 2;
    graphicsPipelineCreateInfo.pStages = shaderStagesCreateInfos;
    graphicsPipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
    graphicsPipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
    graphicsPipelineCreateInfo.pTessellationState = nullptr;
    graphicsPipelineCreateInfo.pViewportState = &viewportStateCreateInfo;
    graphicsPipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
    graphicsPipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
    graphicsPipelineCreateInfo.pDepthStencilState = nullptr;
    graphicsPipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo;
    graphicsPipelineCreateInfo.pDynamicState = nullptr;
    graphicsPipelineCreateInfo.layout = layout;
    graphicsPipelineCreateInfo.renderPass = renderPass;
    graphicsPipelineCreateInfo.subpass = 0;
    graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    graphicsPipelineCreateInfo.basePipelineIndex = -1;

    VkPipeline pipeline;
    result = vkCreateGraphicsPipelines(*device.GetVkDevice(), VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, &pipeline);
    HK_ASSERT_VK(result);

    std::vector<VkFramebuffer> framebuffers(imagesInSwapchainCount);
    for(int i = 0; i < imagesInSwapchainCount; ++i) {
        VkFramebufferCreateInfo framebufferCreateInfo;
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.pNext = nullptr;
        framebufferCreateInfo.flags = 0;
        framebufferCreateInfo.renderPass = renderPass;
        framebufferCreateInfo.attachmentCount = 1;
        framebufferCreateInfo.pAttachments = &imageViews.at(i);
        framebufferCreateInfo.width = window.GetWindowCreateInfo()->width;
        framebufferCreateInfo.height = window.GetWindowCreateInfo()->height;
        framebufferCreateInfo.layers = 1;

        result = vkCreateFramebuffer(*device.GetVkDevice(), &framebufferCreateInfo, nullptr, &framebuffers.at(i));
        HK_ASSERT_VK(result);
    }

    VkCommandPoolCreateInfo commandPoolCreateInfo;
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.pNext = nullptr;
    commandPoolCreateInfo.flags = 0;
    commandPoolCreateInfo.queueFamilyIndex = 0;

    VkCommandPool commandPool;
    result = vkCreateCommandPool(*device.GetVkDevice(), &commandPoolCreateInfo, nullptr, &commandPool);
    HK_ASSERT_VK(result);

    VkDeviceSize vertexBufferSize = sizeof(hk::vertices.at(0)) * hk::vertices.size();
    
    hk::BufferCreateInfo firstStagingBufferCreateInfo;
    firstStagingBufferCreateInfo.pNext = nullptr;
    firstStagingBufferCreateInfo.size = vertexBufferSize;
    firstStagingBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    firstStagingBufferCreateInfo.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    hk::Buffer firstStagingBuffer(&physicalDevice, &device, &firstStagingBufferCreateInfo);

    void* firstRawData;
    vkMapMemory(*device.GetVkDevice(), *firstStagingBuffer.GetBufferMemory(), 0, vertexBufferSize, 0, &firstRawData);
    std::memcpy(firstRawData, hk::vertices.data(), vertexBufferSize);
    vkUnmapMemory(*device.GetVkDevice(), *firstStagingBuffer.GetBufferMemory());

    hk::BufferCreateInfo vertexBufferCreateInfo;
    vertexBufferCreateInfo.pNext = nullptr;
    vertexBufferCreateInfo.size = vertexBufferSize;
    vertexBufferCreateInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    vertexBufferCreateInfo.properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    hk::Buffer vertexBuffer(&physicalDevice, &device, &vertexBufferCreateInfo);

    hk::CopyBuffer(device.GetVkDevice(), &commandPool, &graphicsQueue, *firstStagingBuffer.GetBuffer(), *vertexBuffer.GetBuffer(), vertexBufferSize);
    firstStagingBuffer.Destroy();

    VkDeviceSize indexBufferSize = sizeof(hk::indices.at(0)) * hk::indices.size();
        
    hk::BufferCreateInfo secondStagingBufferCreateInfo;
    secondStagingBufferCreateInfo.pNext = nullptr;
    secondStagingBufferCreateInfo.size = indexBufferSize;
    secondStagingBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    secondStagingBufferCreateInfo.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    hk::Buffer secondStagingBuffer(&physicalDevice, &device, &secondStagingBufferCreateInfo);

    void* secondRawData;
    vkMapMemory(*device.GetVkDevice(), *secondStagingBuffer.GetBufferMemory(), 0, indexBufferSize, 0, &secondRawData);
    std::memcpy(secondRawData, hk::indices.data(), indexBufferSize);
    vkUnmapMemory(*device.GetVkDevice(), *secondStagingBuffer.GetBufferMemory());

    hk::BufferCreateInfo indexBufferCreateInfo;
    indexBufferCreateInfo.pNext = nullptr;
    indexBufferCreateInfo.size = indexBufferSize;
    indexBufferCreateInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    indexBufferCreateInfo.properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    hk::Buffer indexBuffer(&physicalDevice, &device, &indexBufferCreateInfo);

    hk::CopyBuffer(device.GetVkDevice(), &commandPool, &graphicsQueue, *secondStagingBuffer.GetBuffer(), *indexBuffer.GetBuffer(), indexBufferSize);
    secondStagingBuffer.Destroy();

    VkDeviceSize uniformBufferSize = sizeof(hk::UBO);

    hk::BufferCreateInfo uniformBufferCreateInfo;
    uniformBufferCreateInfo.pNext = nullptr;
    uniformBufferCreateInfo.size = uniformBufferSize;
    uniformBufferCreateInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    uniformBufferCreateInfo.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    hk::Buffer uniformBuffer(&physicalDevice, &device, &uniformBufferCreateInfo);

    VkDescriptorPoolSize descriptorPoolSize;
    descriptorPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorPoolSize.descriptorCount = 1;

    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo;
    descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descriptorPoolCreateInfo.pNext = nullptr;
    descriptorPoolCreateInfo.flags = 0;
    descriptorPoolCreateInfo.poolSizeCount = 1;
    descriptorPoolCreateInfo.pPoolSizes = &descriptorPoolSize;
    descriptorPoolCreateInfo.maxSets = 1;

    VkDescriptorPool descriptorPool;
    result = vkCreateDescriptorPool(*device.GetVkDevice(), &descriptorPoolCreateInfo, nullptr, &descriptorPool);
    HK_ASSERT_VK(result);

    VkDescriptorSetAllocateInfo descriptorSetAllocateInfo;
    descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorSetAllocateInfo.pNext = nullptr;
    descriptorSetAllocateInfo.descriptorPool = descriptorPool;
    descriptorSetAllocateInfo.descriptorSetCount = 1;
    descriptorSetAllocateInfo.pSetLayouts = &descriptorSetLayout;

    VkDescriptorSet descriptorSet;
    result = vkAllocateDescriptorSets(*device.GetVkDevice(), &descriptorSetAllocateInfo, &descriptorSet);
    HK_ASSERT_VK(result);

    VkDescriptorBufferInfo descriptorBufferInfo;
    descriptorBufferInfo.buffer = *uniformBuffer.GetBuffer();
    descriptorBufferInfo.offset = 0;
    descriptorBufferInfo.range = sizeof(hk::UBO);

    VkWriteDescriptorSet writeDescriptorSet;
    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSet.pNext = nullptr;
    writeDescriptorSet.dstSet = descriptorSet;
    writeDescriptorSet.dstBinding = 0;
    writeDescriptorSet.dstArrayElement = 0;
    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    writeDescriptorSet.descriptorCount = 1;
    writeDescriptorSet.pBufferInfo = &descriptorBufferInfo;
    writeDescriptorSet.pImageInfo = nullptr;
    writeDescriptorSet.pTexelBufferView = nullptr;

    vkUpdateDescriptorSets(*device.GetVkDevice(), 1, &writeDescriptorSet, 0, nullptr);

    VkCommandBufferAllocateInfo commandBufferAllocateInfo;
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.pNext = nullptr;
    commandBufferAllocateInfo.commandPool = commandPool;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.commandBufferCount = imagesInSwapchainCount;

    std::vector<VkCommandBuffer> commandBuffers(imagesInSwapchainCount);
    result = vkAllocateCommandBuffers(*device.GetVkDevice(), &commandBufferAllocateInfo, commandBuffers.data());
    HK_ASSERT_VK(result);

    VkCommandBufferBeginInfo commandBufferBeginInfo;
    commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBufferBeginInfo.pNext = nullptr;
    commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    commandBufferBeginInfo.pInheritanceInfo = nullptr;

    for(int i = 0; i < imagesInSwapchainCount; ++i) {
        result = vkBeginCommandBuffer(commandBuffers.at(i), &commandBufferBeginInfo);
        HK_ASSERT_VK(result);

        VkRenderPassBeginInfo renderPassBeginInfo;
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.pNext = nullptr;
        renderPassBeginInfo.renderPass = renderPass;
        renderPassBeginInfo.framebuffer = framebuffers.at(i);
        renderPassBeginInfo.renderArea.offset = { 0, 0 };
        renderPassBeginInfo.renderArea.extent = { window.GetWindowCreateInfo()->width, window.GetWindowCreateInfo()->height };
        VkClearValue clearValue = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderPassBeginInfo.clearValueCount = 1;
        renderPassBeginInfo.pClearValues = &clearValue;

        vkCmdBeginRenderPass(commandBuffers.at(i), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers.at(i), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

        VkBuffer vertexBuffers[] = { *vertexBuffer.GetBuffer() };
        VkDeviceSize offsets[] = { 0 };

        vkCmdBindVertexBuffers(commandBuffers.at(i), 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffers.at(i), *indexBuffer.GetBuffer(), offsets[0], VK_INDEX_TYPE_UINT32);
        vkCmdBindDescriptorSets(commandBuffers.at(i), VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &descriptorSet, 0, nullptr);

        vkCmdDrawIndexed(commandBuffers.at(i), hk::indices.size(), 1, 0, 0, 0);

        vkCmdEndRenderPass(commandBuffers.at(i));

        result = vkEndCommandBuffer(commandBuffers.at(i));
        HK_ASSERT_VK(result);
    }

    VkSemaphoreCreateInfo semaphoreCreateInfo;
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreCreateInfo.pNext = nullptr;
    semaphoreCreateInfo.flags = 0;

    VkSemaphore semaphoreImageAvailable;
    result = vkCreateSemaphore(*device.GetVkDevice(), &semaphoreCreateInfo, nullptr, &semaphoreImageAvailable);
    HK_ASSERT_VK(result);

    VkSemaphore semaphoreRenderingDone;
    result = vkCreateSemaphore(*device.GetVkDevice(), &semaphoreCreateInfo, nullptr, &semaphoreRenderingDone);
    HK_ASSERT_VK(result);

    hk::Float_t rotationTime = 0.0f;
    hk::Clock rotationClock;
    while(true) {
        hk::Uint_t imageIndex = 0;
        vkAcquireNextImageKHR(*device.GetVkDevice(), swapchain, std::numeric_limits<hk::Uint64_t>::infinity(), semaphoreImageAvailable, VK_NULL_HANDLE, &imageIndex);

        rotationTime = std::chrono::duration<hk::Float_t, std::chrono::seconds::period>(std::chrono::steady_clock::now() - *rotationClock.GetStartPoint()).count();

        hk::UBO ubo;
        ubo.model = hk::Identity<hk::Float_t>();
        hk::Rotate(ubo.model, rotationTime * hk::radians(90.0f) * 2.0f, hk::Vec3f(0.0f, 0.0f, 1.0f));
        ubo.view = hk::LookAt<hk::Float_t>(hk::Vec3f(2.0f, 2.0f, 2.0f), hk::Vec3f(0.0f, 0.0f, 0.0f), hk::Vec3f(0.0f, 0.0f, 1.0f));
        ubo.projection = hk::Projection(hk::radians(45.0f), (hk::Float_t)(window.GetWindowCreateInfo()->width / window.GetWindowCreateInfo()->height), 0.1f, 1000.0f);
        ubo.projection.matrix[1][1] *= -1;

        void* thirdRawData;
        vkMapMemory(*device.GetVkDevice(), *uniformBuffer.GetBufferMemory(), 0, sizeof(ubo), 0, &thirdRawData);
        std::memcpy(thirdRawData, &ubo, sizeof(ubo));
        vkUnmapMemory(*device.GetVkDevice(), *uniformBuffer.GetBufferMemory());

        VkSubmitInfo submitInfo;
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.pNext = nullptr;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &semaphoreImageAvailable;
        VkPipelineStageFlags waitStageMask[1] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.pWaitDstStageMask = waitStageMask;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffers.at(imageIndex);
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &semaphoreRenderingDone;

        result = vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        HK_ASSERT_VK(result);

        VkPresentInfoKHR presentInfo;
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.pNext = nullptr;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &semaphoreRenderingDone;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &swapchain;
        presentInfo.pImageIndices = &imageIndex;
        presentInfo.pResults = nullptr;

        result = vkQueuePresentKHR(presentQueue, &presentInfo);
        HK_ASSERT_VK(result);

        ++fps;
        if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - *clock.GetStartPoint()) >= std::chrono::seconds(1)) {
            clock.Restart();
            std::string formatFps = "FPS: " + std::to_string(fps);
            hk::Logger::Log(hk::LoggerSeriousness::Info, formatFps);
            fps = 0;
        }

        window.Update();

        vkQueueWaitIdle(graphicsQueue);
    }

    vkDeviceWaitIdle(*device.GetVkDevice());

    vkDestroySemaphore(*device.GetVkDevice(), semaphoreImageAvailable, nullptr);
    vkDestroySemaphore(*device.GetVkDevice(), semaphoreRenderingDone, nullptr);

    vkFreeCommandBuffers(*device.GetVkDevice(), commandPool, commandBuffers.size(), commandBuffers.data());
    commandBuffers.clear();

    vkDestroyCommandPool(*device.GetVkDevice(), commandPool, nullptr);

    for(int i = 0; i < imagesInSwapchainCount; ++i) {
        vkDestroyFramebuffer(*device.GetVkDevice(), framebuffers.at(i), nullptr);
    }
    framebuffers.clear();

    vkDestroyPipeline(*device.GetVkDevice(), pipeline, nullptr);
    vkDestroyRenderPass(*device.GetVkDevice(), renderPass, nullptr);

    for(int i = 0; i < imageViews.size(); ++i) {
        vkDestroyImageView(*device.GetVkDevice(), imageViews.at(i), nullptr);
    }
    imageViews.clear();

    vkDestroyPipelineLayout(*device.GetVkDevice(), layout, nullptr);

    vkDestroyShaderModule(*device.GetVkDevice(), vertexShaderModule, nullptr);
    vkDestroyShaderModule(*device.GetVkDevice(), fragmentShaderModule, nullptr);

    vkDestroyDescriptorSetLayout(*device.GetVkDevice(), descriptorSetLayout, nullptr);
    vkDestroyDescriptorPool(*device.GetVkDevice(), descriptorPool, nullptr);

    vkDestroySwapchainKHR(*device.GetVkDevice(), swapchain, nullptr);

    uniformBuffer.Destroy();
    indexBuffer.Destroy();
    vertexBuffer.Destroy();

    device.Destroy();
    surface.Destroy();
    window.Destroy();

    debugMessenger.DestroyVkMessenger();
    instance.Destroy();

    std::cin.get();
    return 0;
}
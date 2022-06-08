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
        Vec2f texCoord;

        static VkVertexInputBindingDescription GetVkVertexInputBindingDescription() {
            VkVertexInputBindingDescription _vertexInputBindingDescription;
            _vertexInputBindingDescription.binding = 0;
            _vertexInputBindingDescription.stride = sizeof(Vertex);
            _vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            return _vertexInputBindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> GetVkVertexInputAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> _vertexInputAttributeDescription;

            _vertexInputAttributeDescription.at(0).binding = 0;
            _vertexInputAttributeDescription.at(0).location = 0;
            _vertexInputAttributeDescription.at(0).format = VK_FORMAT_R32G32B32_SFLOAT;
            _vertexInputAttributeDescription.at(0).offset = offsetof(Vertex, position);

            _vertexInputAttributeDescription.at(1).binding = 0;
            _vertexInputAttributeDescription.at(1).location = 1;
            _vertexInputAttributeDescription.at(1).format = VK_FORMAT_R32G32B32A32_SFLOAT;
            _vertexInputAttributeDescription.at(1).offset = offsetof(Vertex, color);

            _vertexInputAttributeDescription.at(2).binding = 0;
            _vertexInputAttributeDescription.at(2).location = 2;
            _vertexInputAttributeDescription.at(2).format = VK_FORMAT_R32G32_SFLOAT;
            _vertexInputAttributeDescription.at(2).offset = offsetof(Vertex, texCoord);

            return _vertexInputAttributeDescription;
        }
    };

    const std::vector<Vertex> vertices = {
        {{ -1.0f, -1.0f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }},
        {{  1.0f, -1.0f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }},
        {{  1.0f,  1.0f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }},
        {{ -1.0f,  1.0f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},

        /* {{  1.0f, 1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }},
        {{ -1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }},
        {{ -1.0f, 1.0f,  1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }},
        {{  1.0f, 1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},

        {{ -1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }},
        {{  1.0f, -1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }},
        {{  1.0f, -1.0f,  1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }},
        {{ -1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }}, */

        {{ -1.0f, -1.0f, -1.75f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }},
        {{  1.0f, -1.0f, -1.75f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }},
        {{  1.0f,  1.0f, -1.75f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }},
        {{ -1.0f,  1.0f, -1.75f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},

        /* {{  1.0f, -1.0f,  1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }},
        {{  1.0f, -1.0f,  1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }},
        {{  1.0f,  1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }},
        {{  1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }},

        {{ -1.0f,  1.0f,  1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }},
        {{ -1.0f,  1.0f,  1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }},
        {{ -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }},
        {{ -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }}, */
    };

    const std::vector<Uint_t> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        /* 8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20, */
    };

    VkCommandBuffer HK_API BeginSingleCommandBuffer(Device* pDevice, VkCommandPool* pCommandPool) {
        VkCommandBufferAllocateInfo _commandBufferAllocateInfo;
        _commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        _commandBufferAllocateInfo.pNext = nullptr;
        _commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        _commandBufferAllocateInfo.commandPool = *pCommandPool;
        _commandBufferAllocateInfo.commandBufferCount = 1;

        VkCommandBuffer _commandBuffer;
        result = vkAllocateCommandBuffers(*pDevice->GetVkDevice(), &_commandBufferAllocateInfo, &_commandBuffer);
        HK_ASSERT_VK(result);

        VkCommandBufferBeginInfo _commandBufferBeginInfo;
        _commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        _commandBufferBeginInfo.pNext = nullptr;
        _commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        _commandBufferBeginInfo.pInheritanceInfo = nullptr;

        result = vkBeginCommandBuffer(_commandBuffer, &_commandBufferBeginInfo);
        HK_ASSERT_VK(result);

        return _commandBuffer;
    }

    void HK_API EndSingleCommandBuffer(Device* pDevice, VkCommandPool* pCommandPool, VkCommandBuffer commandBuffer, VkQueue* pQueue) {
        result = vkEndCommandBuffer(commandBuffer);
        HK_ASSERT_VK(result);

        VkSubmitInfo _submitInfo;
        _submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        _submitInfo.pNext = nullptr;
        _submitInfo.waitSemaphoreCount = 0;
        _submitInfo.pWaitSemaphores = nullptr;
        _submitInfo.pWaitDstStageMask = nullptr;
        _submitInfo.commandBufferCount = 1;
        _submitInfo.pCommandBuffers = &commandBuffer;
        _submitInfo.signalSemaphoreCount = 0;
        _submitInfo.pSignalSemaphores = nullptr;

        result = vkQueueSubmit(*pQueue, 1, &_submitInfo, VK_NULL_HANDLE);
        HK_ASSERT_VK(result);

        vkQueueWaitIdle(*pQueue);

        vkFreeCommandBuffers(*pDevice->GetVkDevice(), *pCommandPool, 1, &commandBuffer);
    }

    void HK_API CopyBuffer(Device* pDevice, VkCommandPool* pCommandPool, VkQueue* pQueue, VkBuffer source, VkBuffer destination, VkDeviceSize size) {
        VkCommandBuffer _commandBuffer = BeginSingleCommandBuffer(pDevice, pCommandPool);

        VkBufferCopy _bufferCopy;
        _bufferCopy.srcOffset = 0;
        _bufferCopy.dstOffset = 0;
        _bufferCopy.size = size;
        vkCmdCopyBuffer(_commandBuffer, source, destination, 1, &_bufferCopy);

        EndSingleCommandBuffer(pDevice, pCommandPool, _commandBuffer, pQueue);
    }

    struct HK_API UBO {
        Mat4f model;
        Mat4f view;
        Mat4f projection;
    };

    void HK_API AllocateRawData(Device* pDevice, Buffer* pBuffer, VkDeviceSize size, const void* data) {
        void* _rawData;
        vkMapMemory(*pDevice->GetVkDevice(), *pBuffer->GetBufferMemory(), 0, size, 0, &_rawData);
        std::memcpy(_rawData, data, size);
        vkUnmapMemory(*pDevice->GetVkDevice(), *pBuffer->GetBufferMemory());
    }

    void HK_API CopyBufferToImage(Device* pDevice, VkCommandPool* pCommandPool, VkQueue* pQueue, VkBuffer source, VkImage destination, Vec2u size) {
        VkCommandBuffer _commandBuffer = BeginSingleCommandBuffer(pDevice, pCommandPool);

        VkBufferImageCopy _bufferImageCopy;
        _bufferImageCopy.bufferOffset = 0;
        _bufferImageCopy.bufferRowLength = 0;
        _bufferImageCopy.bufferImageHeight = 0;
        _bufferImageCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        _bufferImageCopy.imageSubresource.mipLevel = 0;
        _bufferImageCopy.imageSubresource.baseArrayLayer = 0;
        _bufferImageCopy.imageSubresource.layerCount = 1;
        _bufferImageCopy.imageOffset = { 0, 0, 0 };
        _bufferImageCopy.imageExtent = { size.x, size.y, 1 };
        vkCmdCopyBufferToImage(_commandBuffer, source, destination, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &_bufferImageCopy);

        EndSingleCommandBuffer(pDevice, pCommandPool, _commandBuffer, pQueue);
    }

    VkFormat FindSupportedFormat(PhysicalDevice* physicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
        for(auto& format : candidates) {
            VkFormatProperties properties;
            vkGetPhysicalDeviceFormatProperties(*physicalDevice->GetVkPhysicalDevice(), format, &properties);
            if(tiling == VK_IMAGE_TILING_LINEAR && (properties.linearTilingFeatures & features) == features) {
                return format;
            } else if(tiling == VK_IMAGE_TILING_OPTIMAL && (properties.optimalTilingFeatures & features) == features) {
                return format;
            }
        }
    }

    VkFormat FindDepthFormat(PhysicalDevice* physicalDevice) {
        return FindSupportedFormat(physicalDevice, { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT }, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
    }

    bool HasStencilComponent(VkFormat format) {
        return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
    }
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
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 4);
    appInfo.pEngineName = "Hukan";
    appInfo.apiVersion = instanceVersion;

    std::vector<hk::Layer> layers;
    hk::Layers::EnumerateLayers(layers);
    for(auto i = 0; i < layers.size(); ++i) {
        layers.at(i).PrintVkLayerProperties();
    }

    std::vector<hk::Extension> extensions;
    hk::Extensions::EnumerateExtensions(extensions);
    for(int i = 0; i < extensions.size(); ++i) {
        extensions.at(i).PrintVkExtensionProperties();
    }

    std::vector<const hk::Char_t*> usedExtensions;

    usedExtensions.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME);
    #if defined(HUKAN_SYSTEM_WIN32)
        usedExtensions.emplace_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
    #elif defined(HUKAN_SYSTEM_POSIX)
        usedExtensions.emplace_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
    #endif
    usedExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    hk::MessengerCreateInfo messengerCreateInfo;
    messengerCreateInfo.pNext = nullptr;
    messengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    messengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    messengerCreateInfo.pfnUserCallback = (PFN_vkDebugUtilsMessengerCallbackEXT)hk::DebugMessengerCallback;
    messengerCreateInfo.pUserData = nullptr;

    hk::InstanceCreateInfo instanceCreateInfo;
    instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)messengerCreateInfo.GetVkMessengerCreateInfo();
    instanceCreateInfo.pAppInfo = &appInfo;

    #if defined(HK_ENABLE_VALIDATION_LAYERS)
        instanceCreateInfo.enabledLayersCount = hk::g_validationLayers.size();
        instanceCreateInfo.ppEnabledLayers = hk::g_validationLayers.data();
    #else
        instanceCreateInfo.enabledLayersCount = 0;
        instanceCreateInfo.ppEnabledLayers = nullptr;
    #endif

    instanceCreateInfo.enabledExtensionsCount = usedExtensions.size();
    instanceCreateInfo.ppEnabledExtensions = usedExtensions.data();

    for(auto i = 0; i < instanceCreateInfo.enabledLayersCount; ++i) {
        hk::Logger::Log(hk::LoggerSeriousness::Info, std::string("Used Layer: " + std::string(instanceCreateInfo.ppEnabledLayers[i])));
    }
    hk::Logger::Endl();

    for(auto i = 0; i < instanceCreateInfo.enabledExtensionsCount; ++i) {
        hk::Logger::Log(hk::LoggerSeriousness::Info, std::string("Used Extension: " + std::string(instanceCreateInfo.ppEnabledExtensions[i])));
    }
    hk::Logger::Endl();

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
    std::vector<hk::PhysicalDevice> physicalDevices;
    hk::PhysicalDevices::EnumeratePhysicalDevices(instance, physicalDevicesCount, physicalDevices);

    hk::PhysicalDevice physicalDevice(physicalDevices.at(0).GetVkPhysicalDevice());
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

    VkPhysicalDeviceFeatures usedFeatures;
    vkGetPhysicalDeviceFeatures(*physicalDevice.GetVkPhysicalDevice(), &usedFeatures);

    std::vector<const hk::Char_t*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    hk::DeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.pNext = nullptr;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    deviceCreateInfo.enabledLayerCount = 0;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;
    deviceCreateInfo.enabledExtensionCount = deviceExtensions.size();
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
    deviceCreateInfo.pEnabledFeatures = &usedFeatures;

    hk::Device device(&physicalDevice, &deviceCreateInfo);

    hk::SurfaceCapabilities surfaceCapabilities;
    hk::GetSurfaceCapabilities(&physicalDevice, &surface, &surfaceCapabilities);

    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface minImageCount: " + std::to_string(surfaceCapabilities.minImageCount));
    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface maxImageCount: " + std::to_string(surfaceCapabilities.maxImageCount));
    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface currentExtent: " + std::to_string(surfaceCapabilities.currentExtent.x) + "/" + std::to_string(surfaceCapabilities.currentExtent.y));
    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface minImageExtent: " + std::to_string(surfaceCapabilities.minImageExtent.x) + "/" + std::to_string(surfaceCapabilities.minImageExtent.y));
    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface maxImageExtent: " + std::to_string(surfaceCapabilities.maxImageExtent.x) + "/" + std::to_string(surfaceCapabilities.maxImageExtent.y));
    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface maxImageArrayLayers: " + std::to_string(surfaceCapabilities.maxImageArrayLayers));
    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface supportedTransforms: " + std::to_string(surfaceCapabilities.supportedTransforms));
    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface currentTransform: " + std::to_string(surfaceCapabilities.currentTransform));
    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface supportedCompositeAlpha: " + std::to_string(surfaceCapabilities.supportedCompositeAlpha));
    hk::Logger::Log(hk::LoggerSeriousness::Info, "Surface supportedUsageFlags: " + std::to_string(surfaceCapabilities.supportedUsageFlags));
    hk::Logger::Endl();

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

            VkBool32 surfaceSupport = false;
            result = vkGetPhysicalDeviceSurfaceSupportKHR(*physicalDevice.GetVkPhysicalDevice(), i, *surface.GetVkSurfaceKHR(), &surfaceSupport);
            HK_ASSERT_VK(result);

            if(surfaceSupport) {
                presentQueueCount = graphicsQueueCount;
                hk::Logger::Log(hk::LoggerSeriousness::Info, std::string("Surface Is Supported: " + std::to_string(i)));
            } else {
                hk::Logger::Log(hk::LoggerSeriousness::Critical, std::string("Surface Is Not Supported: " + std::to_string(i)));
            }
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

    VkDescriptorSetLayoutBinding samplerSetLayoutBinding;
    samplerSetLayoutBinding.binding = 1;
    samplerSetLayoutBinding.descriptorCount = 1;
    samplerSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerSetLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    samplerSetLayoutBinding.pImmutableSamplers = nullptr;

    std::array<VkDescriptorSetLayoutBinding, 2> bindings = { descriptorSetLayoutBinding, samplerSetLayoutBinding };
    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo;
    descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetLayoutCreateInfo.pNext = nullptr;
    descriptorSetLayoutCreateInfo.flags = 0;
    descriptorSetLayoutCreateInfo.bindingCount = bindings.size();
    descriptorSetLayoutCreateInfo.pBindings = bindings.data();

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
    rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE; // VK_FRONT_FACE_CLOCKWISE;
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

    VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo;
    depthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilStateCreateInfo.pNext = nullptr;
    depthStencilStateCreateInfo.flags = 0;
    depthStencilStateCreateInfo.depthTestEnable = VK_TRUE;
    depthStencilStateCreateInfo.depthWriteEnable = VK_TRUE;
    depthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS;
    depthStencilStateCreateInfo.depthBoundsTestEnable = VK_FALSE;
    depthStencilStateCreateInfo.minDepthBounds = 0.0f;
    depthStencilStateCreateInfo.maxDepthBounds = 1.0f;
    depthStencilStateCreateInfo.stencilTestEnable = VK_FALSE;
    depthStencilStateCreateInfo.front = { };
    depthStencilStateCreateInfo.back = { };

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

    VkAttachmentDescription colorAttachmentDescription;
    colorAttachmentDescription.flags = 0;
    colorAttachmentDescription.format = VK_FORMAT_B8G8R8A8_SRGB;
    colorAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentDescription depthAttachmentDescription;
    depthAttachmentDescription.flags = 0;
    depthAttachmentDescription.format = hk::FindDepthFormat(&physicalDevice);
    depthAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    depthAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depthAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorAttachmentReference;
    colorAttachmentReference.attachment = 0;
    colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthAttachmentReference;
    depthAttachmentReference.attachment = 1;
    depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpassDescription;
    subpassDescription.flags = 0;
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.inputAttachmentCount = 0;
    subpassDescription.pInputAttachments = nullptr;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &colorAttachmentReference;
    subpassDescription.pResolveAttachments = nullptr;
    subpassDescription.pDepthStencilAttachment = &depthAttachmentReference;
    subpassDescription.preserveAttachmentCount = 0;
    subpassDescription.pPreserveAttachments = nullptr;

    VkSubpassDependency subpassDependency;
    subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependency.dstSubpass = 0;
    subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    subpassDependency.srcAccessMask = 0;
    subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    subpassDependency.dependencyFlags = 0;

    std::array<VkAttachmentDescription, 2> attachments = { colorAttachmentDescription, depthAttachmentDescription };
    VkRenderPassCreateInfo renderPassCreateInfo;
    renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.pNext = nullptr;
    renderPassCreateInfo.flags = 0;
    renderPassCreateInfo.attachmentCount = attachments.size();
    renderPassCreateInfo.pAttachments = attachments.data();
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
    graphicsPipelineCreateInfo.pDepthStencilState = &depthStencilStateCreateInfo;
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

    VkCommandPoolCreateInfo commandPoolCreateInfo;
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.pNext = nullptr;
    commandPoolCreateInfo.flags = 0;
    commandPoolCreateInfo.queueFamilyIndex = 0;

    VkCommandPool commandPool;
    result = vkCreateCommandPool(*device.GetVkDevice(), &commandPoolCreateInfo, nullptr, &commandPool);
    HK_ASSERT_VK(result);

    VkFormat depthFormat = hk::FindDepthFormat(&physicalDevice);

    VkImageCreateInfo depthImageCreateInfo;
    depthImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    depthImageCreateInfo.pNext = nullptr;
    depthImageCreateInfo.flags = 0;
    depthImageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
    depthImageCreateInfo.extent = { window.GetWindowCreateInfo()->width, window.GetWindowCreateInfo()->height, 1 };
    depthImageCreateInfo.mipLevels = 1;
    depthImageCreateInfo.arrayLayers = 1;
    depthImageCreateInfo.format = depthFormat;
    depthImageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    depthImageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthImageCreateInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    depthImageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    depthImageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;

    VkImage depthTextureImage;
    result = vkCreateImage(*device.GetVkDevice(), &depthImageCreateInfo, nullptr, &depthTextureImage);
    HK_ASSERT_VK(result);

    VkMemoryRequirements depthTextureMemoryRequirements;
    vkGetImageMemoryRequirements(*device.GetVkDevice(), depthTextureImage, &depthTextureMemoryRequirements);

    VkMemoryAllocateInfo depthTextureMemoryAllocateInfo;
    depthTextureMemoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    depthTextureMemoryAllocateInfo.pNext = nullptr;
    depthTextureMemoryAllocateInfo.allocationSize = depthTextureMemoryRequirements.size;
    depthTextureMemoryAllocateInfo.memoryTypeIndex = hk::FindMemoryType(*physicalDevice.GetVkPhysicalDevice(), depthTextureMemoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    VkDeviceMemory depthImageDeviceMemory;
    result = vkAllocateMemory(*device.GetVkDevice(), &depthTextureMemoryAllocateInfo, nullptr, &depthImageDeviceMemory);
    HK_ASSERT_VK(result);

    vkBindImageMemory(*device.GetVkDevice(), depthTextureImage, depthImageDeviceMemory, 0);

    VkImageViewCreateInfo depthImageViewCreateInfo;
    depthImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    depthImageViewCreateInfo.pNext = nullptr;
    depthImageViewCreateInfo.flags = 0;
    depthImageViewCreateInfo.image = depthTextureImage;
    depthImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    depthImageViewCreateInfo.format = depthFormat;
    depthImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    depthImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    depthImageViewCreateInfo.subresourceRange.levelCount = 1;
    depthImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    depthImageViewCreateInfo.subresourceRange.layerCount = 1;
    depthImageViewCreateInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };

    VkImageView depthImageView;
    result = vkCreateImageView(*device.GetVkDevice(), &depthImageViewCreateInfo, nullptr, &depthImageView);
    HK_ASSERT_VK(result);

    VkCommandBuffer depthCommandBuffer = hk::BeginSingleCommandBuffer(&device, &commandPool);

    VkImageMemoryBarrier depthImageMemoryBarrier;
    depthImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    depthImageMemoryBarrier.pNext = nullptr;
    depthImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    depthImageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    depthImageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    depthImageMemoryBarrier.image = depthTextureImage;
    depthImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    if(hk::HasStencilComponent(depthFormat)) {
        depthImageMemoryBarrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
    }
    depthImageMemoryBarrier.subresourceRange.baseMipLevel = 0;
    depthImageMemoryBarrier.subresourceRange.levelCount = 1;
    depthImageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
    depthImageMemoryBarrier.subresourceRange.layerCount = 1;
    depthImageMemoryBarrier.srcAccessMask = 0;
    depthImageMemoryBarrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    
    vkCmdPipelineBarrier(depthCommandBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT, 0, 0, nullptr, 0, nullptr, 1, &depthImageMemoryBarrier);

    hk::EndSingleCommandBuffer(&device, &commandPool, depthCommandBuffer, &graphicsQueue);

    std::vector<VkFramebuffer> framebuffers(imagesInSwapchainCount);
    for(int i = 0; i < imagesInSwapchainCount; ++i) {
        std::array<VkImageView, 2> attachments = { imageViews.at(i), depthImageView };

        VkFramebufferCreateInfo framebufferCreateInfo;
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.pNext = nullptr;
        framebufferCreateInfo.flags = 0;
        framebufferCreateInfo.renderPass = renderPass;
        framebufferCreateInfo.attachmentCount = attachments.size();
        framebufferCreateInfo.pAttachments = attachments.data();
        framebufferCreateInfo.width = window.GetWindowCreateInfo()->width;
        framebufferCreateInfo.height = window.GetWindowCreateInfo()->height;
        framebufferCreateInfo.layers = 1;

        result = vkCreateFramebuffer(*device.GetVkDevice(), &framebufferCreateInfo, nullptr, &framebuffers.at(i));
        HK_ASSERT_VK(result);
    }

    int textureWidth, textureHeight, textureChannels;
    stbi_uc* pixels = stbi_load("res/test.jpg", &textureWidth, &textureHeight, &textureChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = textureWidth * textureHeight * 4;

    if(!pixels) {
        hk::Logger::Log(hk::LoggerSeriousness::Error, "Failed Texture Loading");
        hk::Logger::Endl();
    }

    hk::BufferCreateInfo textureStagingBufferCreateInfo;
    textureStagingBufferCreateInfo.pNext = nullptr;
    textureStagingBufferCreateInfo.size = imageSize;
    textureStagingBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    textureStagingBufferCreateInfo.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    hk::Buffer textureStagingBuffer(&physicalDevice, &device, &textureStagingBufferCreateInfo);
    hk::AllocateRawData(&device, &textureStagingBuffer, imageSize, pixels);

    stbi_image_free(pixels);

    VkImageCreateInfo imageCreateInfo;
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.pNext = nullptr;
    imageCreateInfo.flags = 0;
    imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
    imageCreateInfo.extent = { (hk::Uint_t)textureWidth, (hk::Uint_t)textureHeight, 1 };
    imageCreateInfo.mipLevels = 1;
    imageCreateInfo.arrayLayers = 1;
    imageCreateInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageCreateInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;

    VkImage textureImage;
    result = vkCreateImage(*device.GetVkDevice(), &imageCreateInfo, nullptr, &textureImage);
    HK_ASSERT_VK(result);

    VkMemoryRequirements textureMemoryRequirements;
    vkGetImageMemoryRequirements(*device.GetVkDevice(), textureImage, &textureMemoryRequirements);

    VkMemoryAllocateInfo textureMemoryAllocateInfo;
    textureMemoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    textureMemoryAllocateInfo.pNext = nullptr;
    textureMemoryAllocateInfo.allocationSize = textureMemoryRequirements.size;
    textureMemoryAllocateInfo.memoryTypeIndex = hk::FindMemoryType(*physicalDevice.GetVkPhysicalDevice(), textureMemoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    VkDeviceMemory imageDeviceMemory;
    result = vkAllocateMemory(*device.GetVkDevice(), &textureMemoryAllocateInfo, nullptr, &imageDeviceMemory);
    HK_ASSERT_VK(result);

    vkBindImageMemory(*device.GetVkDevice(), textureImage, imageDeviceMemory, 0);

    VkCommandBuffer imageCommandBuffer = hk::BeginSingleCommandBuffer(&device, &commandPool);

    VkImageMemoryBarrier imageMemoryBarrier;
    imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    imageMemoryBarrier.pNext = nullptr;
    imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imageMemoryBarrier.image = textureImage;
    imageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageMemoryBarrier.subresourceRange.baseMipLevel = 0;
    imageMemoryBarrier.subresourceRange.levelCount = 1;
    imageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
    imageMemoryBarrier.subresourceRange.layerCount = 1;
    imageMemoryBarrier.srcAccessMask = 0;
    imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    vkCmdPipelineBarrier(imageCommandBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);

    hk::EndSingleCommandBuffer(&device, &commandPool, imageCommandBuffer, &graphicsQueue);

    hk::CopyBufferToImage(&device, &commandPool, &graphicsQueue, *textureStagingBuffer.GetBuffer(), textureImage, { (hk::Uint_t)textureWidth, (hk::Uint_t)textureHeight });

    VkCommandBuffer secondImageCommandBuffer = hk::BeginSingleCommandBuffer(&device, &commandPool);

    VkImageMemoryBarrier secondImageMemoryBarrier;
    secondImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    secondImageMemoryBarrier.pNext = nullptr;
    secondImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    secondImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    secondImageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    secondImageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    secondImageMemoryBarrier.image = textureImage;
    secondImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    secondImageMemoryBarrier.subresourceRange.baseMipLevel = 0;
    secondImageMemoryBarrier.subresourceRange.levelCount = 1;
    secondImageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
    secondImageMemoryBarrier.subresourceRange.layerCount = 1;
    secondImageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    secondImageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    vkCmdPipelineBarrier(secondImageCommandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &secondImageMemoryBarrier);

    hk::EndSingleCommandBuffer(&device, &commandPool, secondImageCommandBuffer, &graphicsQueue);

    textureStagingBuffer.Destroy();

    VkImageViewCreateInfo imageViewCreateInfo;
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.pNext = nullptr;
    imageViewCreateInfo.flags = 0;
    imageViewCreateInfo.image = textureImage;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount = 1;

    VkImageView textureImageView;
    result = vkCreateImageView(*device.GetVkDevice(), &imageViewCreateInfo, nullptr, &textureImageView);
    HK_ASSERT_VK(result);

    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(*physicalDevice.GetVkPhysicalDevice(), &physicalDeviceProperties);

    VkSamplerCreateInfo samplerCreateInfo;
    samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerCreateInfo.pNext = nullptr;
    samplerCreateInfo.flags = 0;
    samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
    samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
    samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerCreateInfo.anisotropyEnable = usedFeatures.samplerAnisotropy;
    samplerCreateInfo.maxAnisotropy = physicalDeviceProperties.limits.maxSamplerAnisotropy;
    samplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;
    samplerCreateInfo.compareEnable = VK_FALSE;
    samplerCreateInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerCreateInfo.mipLodBias = 0.0f;
    samplerCreateInfo.minLod = 0.0f;
    samplerCreateInfo.maxLod = 0.0f;

    VkSampler textureSampler;
    result = vkCreateSampler(*device.GetVkDevice(), &samplerCreateInfo, nullptr, &textureSampler);
    HK_ASSERT_VK(result);

    VkDeviceSize vertexBufferSize = sizeof(hk::vertices.at(0)) * hk::vertices.size();

    hk::BufferCreateInfo firstStagingBufferCreateInfo;
    firstStagingBufferCreateInfo.pNext = nullptr;
    firstStagingBufferCreateInfo.size = vertexBufferSize;
    firstStagingBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    firstStagingBufferCreateInfo.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    hk::Buffer firstStagingBuffer(&physicalDevice, &device, &firstStagingBufferCreateInfo);
    hk::AllocateRawData(&device, &firstStagingBuffer, vertexBufferSize, hk::vertices.data());

    hk::BufferCreateInfo vertexBufferCreateInfo;
    vertexBufferCreateInfo.pNext = nullptr;
    vertexBufferCreateInfo.size = vertexBufferSize;
    vertexBufferCreateInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    vertexBufferCreateInfo.properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    hk::Buffer vertexBuffer(&physicalDevice, &device, &vertexBufferCreateInfo);

    hk::CopyBuffer(&device, &commandPool, &graphicsQueue, *firstStagingBuffer.GetBuffer(), *vertexBuffer.GetBuffer(), vertexBufferSize);
    firstStagingBuffer.Destroy();

    VkDeviceSize indexBufferSize = sizeof(hk::indices.at(0)) * hk::indices.size();

    hk::BufferCreateInfo secondStagingBufferCreateInfo;
    secondStagingBufferCreateInfo.pNext = nullptr;
    secondStagingBufferCreateInfo.size = indexBufferSize;
    secondStagingBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    secondStagingBufferCreateInfo.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    hk::Buffer secondStagingBuffer(&physicalDevice, &device, &secondStagingBufferCreateInfo);
    hk::AllocateRawData(&device, &secondStagingBuffer, indexBufferSize, hk::indices.data());

    hk::BufferCreateInfo indexBufferCreateInfo;
    indexBufferCreateInfo.pNext = nullptr;
    indexBufferCreateInfo.size = indexBufferSize;
    indexBufferCreateInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    indexBufferCreateInfo.properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    hk::Buffer indexBuffer(&physicalDevice, &device, &indexBufferCreateInfo);

    hk::CopyBuffer(&device, &commandPool, &graphicsQueue, *secondStagingBuffer.GetBuffer(), *indexBuffer.GetBuffer(), indexBufferSize);
    secondStagingBuffer.Destroy();

    VkDeviceSize uniformBufferSize = sizeof(hk::UBO);

    hk::BufferCreateInfo uniformBufferCreateInfo;
    uniformBufferCreateInfo.pNext = nullptr;
    uniformBufferCreateInfo.size = uniformBufferSize;
    uniformBufferCreateInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    uniformBufferCreateInfo.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    hk::Buffer uniformBuffer(&physicalDevice, &device, &uniformBufferCreateInfo);

    std::array<VkDescriptorPoolSize, 2> descriptorsPoolSizes;
    descriptorsPoolSizes.at(0).type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorsPoolSizes.at(0).descriptorCount = 1;
    descriptorsPoolSizes.at(1).type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorsPoolSizes.at(1).descriptorCount = 1;

    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo;
    descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descriptorPoolCreateInfo.pNext = nullptr;
    descriptorPoolCreateInfo.flags = 0;
    descriptorPoolCreateInfo.poolSizeCount = descriptorsPoolSizes.size();
    descriptorPoolCreateInfo.pPoolSizes = descriptorsPoolSizes.data();
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

    VkDescriptorImageInfo descriptorImageInfo;
    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    descriptorImageInfo.imageView = textureImageView;
    descriptorImageInfo.sampler = textureSampler;

    std::array<VkWriteDescriptorSet, 2> writeDescriptorSets;
    writeDescriptorSets.at(0).sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSets.at(0).pNext = nullptr;
    writeDescriptorSets.at(0).dstSet = descriptorSet;
    writeDescriptorSets.at(0).dstBinding = 0;
    writeDescriptorSets.at(0).dstArrayElement = 0;
    writeDescriptorSets.at(0).descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writeDescriptorSets.at(0).descriptorCount = 1;
    writeDescriptorSets.at(0).pBufferInfo = &descriptorBufferInfo;
    writeDescriptorSets.at(0).pImageInfo = nullptr;
    writeDescriptorSets.at(0).pTexelBufferView = nullptr;

    writeDescriptorSets.at(1).sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSets.at(1).pNext = nullptr;
    writeDescriptorSets.at(1).dstSet = descriptorSet;
    writeDescriptorSets.at(1).dstBinding = 1;
    writeDescriptorSets.at(1).dstArrayElement = 0;
    writeDescriptorSets.at(1).descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeDescriptorSets.at(1).descriptorCount = 1;
    writeDescriptorSets.at(1).pBufferInfo = nullptr;
    writeDescriptorSets.at(1).pImageInfo = &descriptorImageInfo;
    writeDescriptorSets.at(1).pTexelBufferView = nullptr;

    vkUpdateDescriptorSets(*device.GetVkDevice(), writeDescriptorSets.size(), writeDescriptorSets.data(), 0, nullptr);

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
        std::array<VkClearValue, 2> clearValues;
        clearValues.at(0).color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
        clearValues.at(1).depthStencil = { 1.0f, 0 };
        renderPassBeginInfo.clearValueCount = clearValues.size();
        renderPassBeginInfo.pClearValues = clearValues.data();

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

    // hk::Float_t rotationTime = 0.0f;
    // hk::Clock rotationClock;

    hk::UBO ubo;
    ubo.model = hk::Identity<hk::Float_t>();
    // hk::Rotate(ubo.model, rotationTime * hk::radians(90.0f) * 2.0f, hk::Vec3f(0.0f, 0.0f, 1.0f));
    ubo.view = hk::LookAt(hk::Vec3f(2.0f, 2.0f, 2.0f), hk::Vec3f(0.0f, 0.0f, 0.0f), hk::Vec3f(0.0f, 0.0f, 1.0f));
    // ubo.view = hk::LookAt(hk::Vec3f(0.0f, 0.0f, 2.0f), hk::Vec3f(0.0f, 0.0f, 1.0f), hk::Vec3f(0.0f, 1.0f, 0.0f));
    ubo.projection = hk::Projection<hk::Float_t>(hk::radians(45.0f), (hk::Float_t)(window.GetWindowCreateInfo()->width / window.GetWindowCreateInfo()->height), 0.1f, 1000.0f);
    // ubo.projection = hk::Ortho2D<hk::Float_t>(-(window.GetWindowCreateInfo()->width / window.GetWindowCreateInfo()->height), (window.GetWindowCreateInfo()->width / window.GetWindowCreateInfo()->height), -1.0f, 1.0f, -1.0f, 1.0f);
    hk::Vec3f position = hk::Vec3f(2.0f, 2.0f, 2.0f);
    hk::Vec3f direction;

    while(true) {
        hk::Uint_t imageIndex = 0;
        vkAcquireNextImageKHR(*device.GetVkDevice(), swapchain, std::numeric_limits<hk::Uint64_t>::infinity(), semaphoreImageAvailable, VK_NULL_HANDLE, &imageIndex);

        // rotationTime = std::chrono::duration<hk::Float_t, std::chrono::seconds::period>(std::chrono::steady_clock::now() - *rotationClock.GetStartPoint()).count();
        hk::Rotate(ubo.model, hk::radians(0.1f), hk::Vec3f(0.0f, 0.0f, 1.0f));

        if(window.GetKeyState(VK_UP)) {
            // hk::Rotate(ubo.view, hk::radians(0.05f), hk::Vec3f(0.0f, 0.0f, 1.0f));
            hk::Translate(ubo.view, hk::Vec3f(0.0f, -0.005f, 0.0f));
        } else if(window.GetKeyState(VK_DOWN)) {
            // hk::Rotate(ubo.view, -hk::radians(0.05f), hk::Vec3f(0.0f, 0.0f, 1.0f));
            hk::Translate(ubo.view, hk::Vec3f(0.0f, 0.005f, 0.0f));
        }

        if(window.GetKeyState(VK_LEFT)) {
            // hk::Rotate(ubo.view, -hk::radians(0.05f), hk::Vec3f(1.0f, 0.0f, 0.0f));
            hk::Translate(ubo.view, hk::Vec3f(-0.005f, 0.0f, 0.0f));
        } else if(window.GetKeyState(VK_RIGHT)) {
            // hk::Rotate(ubo.view, hk::radians(0.05f), hk::Vec3f(1.0f, 0.0f, 0.0f));
            hk::Translate(ubo.view, hk::Vec3f(0.005f, 0.0f, 0.0f));
        }

        if(window.GetKeyState('W')) {
            hk::Rotate(ubo.model, hk::radians(0.1f), hk::Vec3f(1.0f, 0.0f, 0.0f));
        } else if(window.GetKeyState('S')) {
            hk::Rotate(ubo.model, -hk::radians(0.1f), hk::Vec3f(1.0f, 0.0f, 0.0f));
        }

        hk::AllocateRawData(&device, &uniformBuffer, sizeof(ubo), &ubo);

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

    vkDestroySampler(*device.GetVkDevice(), textureSampler, nullptr);

    vkDestroyImageView(*device.GetVkDevice(), textureImageView, nullptr);

    vkDestroyImage(*device.GetVkDevice(), textureImage, nullptr);
    vkFreeMemory(*device.GetVkDevice(), imageDeviceMemory, nullptr);

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
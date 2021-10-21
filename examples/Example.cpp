#include <Hukan/Hukan.hpp>

VkResult result;

int main(int argc, char** argv) {
    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pApplicationName = "Hukan-Example";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 2);
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

    hk::Logger::Endl();
    hk::Logger::Endl();

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

    VkDeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext = nullptr;
    deviceCreateInfo.flags = 0;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    deviceCreateInfo.enabledLayerCount = 0;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;
    deviceCreateInfo.enabledExtensionCount = 0;
    deviceCreateInfo.ppEnabledExtensionNames = nullptr;
    deviceCreateInfo.pEnabledFeatures = &usedFeatures;

    VkDevice device;
    result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
    HK_ASSERT(result);

    VkQueue queue;
    vkGetDeviceQueue(device, 0, 0, &queue);

    window.Update();

    vkDeviceWaitIdle(device);

    vkDestroyDevice(device, nullptr);
    surface.Destroy();
    window.Destroy();

    debugMessenger.DestroyVkMessenger();
    instance.DestroyVkInstance();

    std::cin.get();
    return 0;
}
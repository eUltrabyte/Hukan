#include <Hukan/Hukan.hpp>

int main(int argc, char** argv) {
    for(int i = 0; i < argc; ++i) {
        hk::Logger::Log(hk::LoggerSeriousness::Info, argv[i], (hk::Int_t)hk::Color::DarkYellow);
    }

    hk::Logger::Endl();

    for(int i = 0; i < 5; ++i) {
        hk::Logger::Log(hk::LoggerSeriousness(hk::Bit(i)), std::to_string(i));
    }

    hk::Logger::Endl();

    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pApplicationName = "Hukan-Example";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 2);
    appInfo.pEngineName = "Hukan";
    appInfo.apiVersion = VK_API_VERSION_1_0;

    hk::Uint_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> layers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

    for(int i = 0; i < layers.size(); ++i) {
        std::string _format = "instance layers: " + std::string(layers.at(i).layerName);
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format, (hk::Int_t)hk::Color::Blue);
    }

    hk::Logger::Endl();

    hk::Uint_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensionsProperties(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsProperties.data());

    for(int i = 0; i < extensionsProperties.size(); ++i) {
        std::string _format = "instance extension: " + std::string(extensionsProperties.at(i).extensionName);
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format, (hk::Int_t)hk::Color::Blue);
    }

    hk::Logger::Endl();

    std::vector<const hk::Char_t*> extensions;
    for(auto& extension : extensionsProperties) {
        extensions.push_back(extension.extensionName);
    }

    if(HK_ENABLE_VALIDATION_LAYERS) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    hk::Instance instance(nullptr);

    hk::InstanceCreateInfo instanceCreateInfo;
    instanceCreateInfo.pAppInfo = &appInfo;
    instanceCreateInfo.enabledLayersCount = hk::g_validationLayers.size();
    instanceCreateInfo.ppEnabledLayers = hk::g_validationLayers.data();
    instanceCreateInfo.enabledExtensionsCount = extensions.size();
    instanceCreateInfo.ppEnabledExtensions = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT messengerCreateInfo;
    messengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    messengerCreateInfo.pNext = nullptr;
    messengerCreateInfo.flags = 0;
    messengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    messengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    messengerCreateInfo.pfnUserCallback = hk::DebugCallback;
    messengerCreateInfo.pUserData = nullptr;

    VkDebugUtilsMessengerEXT debugMessenger;

    instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugMessenger;

    hk::Logger::CreateMessenger(*instance.GetVkInstance(), &messengerCreateInfo, nullptr, &debugMessenger);

    instance.SetVkInstanceCreateInfo(&instanceCreateInfo);
    instance.CreateVkInstance();

    std::cin.get();

    hk::Logger::DestroyMessenger(*instance.GetVkInstance(), debugMessenger, nullptr);
    return 0;
}
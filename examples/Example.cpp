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
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    for(int i = 0; i < extensions.size(); ++i) {
        std::string _format = "instance extension: " + std::string(extensions.at(i).extensionName);
        hk::Logger::Log(hk::LoggerSeriousness::Info, _format, (hk::Int_t)hk::Color::Blue);
    }

    hk::Logger::Endl();

    hk::InstanceCreateInfo instanceCreateInfo;
    instanceCreateInfo.pAppInfo = &appInfo;
    instanceCreateInfo.enabledLayersCount = 0;
    instanceCreateInfo.ppEnabledLayers = nullptr;
    instanceCreateInfo.enabledExtensionsCount = 0;
    instanceCreateInfo.ppEnabledExtensions = nullptr;

    hk::Instance instance(&instanceCreateInfo);

    std::cin.get();
    return 0;
}
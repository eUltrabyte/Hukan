#include "Logger.hpp"

namespace hk {
    Logger::Logger(const LoggerSeriousness& seriousness, const std::string& format, Int_t color) {
        Log(seriousness, format, color);
    }
    
    Logger::~Logger() {
        delete this;
    }

    void Logger::Log(const LoggerSeriousness& seriousness, const std::string& format, Int_t color) {
        std::tm* _now = Clock::GetActualTime();

        std::string _hours;
        if(_now->tm_hour <= 9) {
            _hours = "0" + std::to_string(_now->tm_hour);
        } else if(_now->tm_hour == 0) {
            _hours = "00";
        } else {
            _hours = std::to_string(_now->tm_hour);
        }

        std::string _minutes;
        if(_now->tm_min <= 9) {
            _minutes = "0" + std::to_string(_now->tm_min);
        } else if(_now->tm_min == 0) {
            _minutes = "00";
        } else {
            _minutes = std::to_string(_now->tm_min);
        }

        std::string _seconds;
        if(_now->tm_sec <= 9) {
            _seconds = "0" + std::to_string(_now->tm_sec);
        } else if(_now->tm_sec == 0) {
            _seconds = "00";
        } else {
            _seconds = std::to_string(_now->tm_sec);
        }

        std::string _loggerFormat, _timeFormat;
        if(seriousness == LoggerSeriousness::None) {
            _timeFormat = "[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ]";
            _loggerFormat = "[ Type: None ]";
            AsColor(Color::Green);
            printf("%s ", _timeFormat.c_str());
            AsColor(Color::Reset);
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        } else if(seriousness == LoggerSeriousness::Info) {
            _timeFormat = "[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ]";
            _loggerFormat = "[ Type: Info ]";
            AsColor(Color::Green);
            printf("%s ", _timeFormat.c_str());
            AsColor(Color::Cyan);
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        } else if(seriousness == LoggerSeriousness::Warning) {
            _timeFormat = "[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ]";
            _loggerFormat = "[ Type: Warning ]";
            AsColor(Color::Green);
            printf("%s ", _timeFormat.c_str());
            AsColor(Color::DarkMagenta);
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        } else if(seriousness == LoggerSeriousness::Error) {
            _timeFormat = "[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ]";
            _loggerFormat = "[ Type: Error ]";
            AsColor(Color::Green);
            printf("%s ", _timeFormat.c_str());
            AsColor(Color::Red);
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        } else if(seriousness == LoggerSeriousness::Critical) {
            _timeFormat = "[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ]";
            _loggerFormat = "[ Type: Critical ]";
            AsColor(Color::Green);
            printf("%s ", _timeFormat.c_str());
            AsColor(Color::DarkRed);
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        }
    }

    void Logger::Endl() {
        printf("\n");
        AsColor(hk::Color::Reset);
    }

    VkResult Logger::CreateMessenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto _func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if(_func != nullptr) {
            return _func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        return VkResult(0);
    }

    void Logger::DestroyMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto _func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if(_func != nullptr) {
            _func(instance, debugMessenger, pAllocator);
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::string _format = "validation layer: " + std::string(pCallbackData->pMessage);
        if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            Logger::Log(LoggerSeriousness::Warning, _format);
        } else if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            Logger::Log(LoggerSeriousness::Error, _format);
        }
        return VK_FALSE;
    }
};
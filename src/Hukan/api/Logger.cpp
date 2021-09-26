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

        std::string _seconds;
        if(_now->tm_sec <= 9) {
            _seconds = "0" + std::to_string(_now->tm_sec);
        } else if(_now->tm_sec == 0) {
            _seconds = "00";
        } else {
            _seconds = std::to_string(_now->tm_sec);
        }

        std::string _loggerFormat;
        if(seriousness == LoggerSeriousness::None) {
            _loggerFormat = "[ Time: " + std::to_string(_now->tm_hour) + ":" + std::to_string(_now->tm_min) + ":" + _seconds + " ] [ Type: NONE ]";
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        } else if(seriousness == LoggerSeriousness::Info) {
            _loggerFormat = "[ Time: " + std::to_string(_now->tm_hour) + ":" + std::to_string(_now->tm_min) + ":" + _seconds + " ] [ Type: INFO ]";
            AsColor(Color::Cyan);
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        } else if(seriousness == LoggerSeriousness::Warning) {
            _loggerFormat = "[ Time: " + std::to_string(_now->tm_hour) + ":" + std::to_string(_now->tm_min) + ":" + _seconds + " ] [ Type: WARNING ]";
            AsColor(Color::DarkMagenta);
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        } else if(seriousness == LoggerSeriousness::Error) {
            _loggerFormat = "[ Time: " + std::to_string(_now->tm_hour) + ":" + std::to_string(_now->tm_min) + ":" + _seconds + " ] [ Type: ERROR ]";
            AsColor(Color::Red);
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        } else if(seriousness == LoggerSeriousness::Critical) {
            _loggerFormat = "[ Time: " + std::to_string(_now->tm_hour) + ":" + std::to_string(_now->tm_min) + ":" + _seconds + " ] [ Type: CRITICAL ]";
            AsColor(Color::DarkRed);
            printf("%s ", _loggerFormat.c_str());
            AsColor(Color(color));
            printf("%s \n", format.c_str());
            AsColor(Color::Reset);
        }
    }

    void Logger::Endl() {
        printf("\n");
        hk::AsColor(hk::Color::Reset);
    }
};
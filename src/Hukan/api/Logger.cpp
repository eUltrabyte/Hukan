#include "Logger.hpp"

namespace hk {
    Logger::Logger(const LoggerSeriousness& seriousness, const std::string& format) {
        Log(seriousness, format);
    }
    
    Logger::~Logger() {
        delete this;
    }

    void Logger::Log(const LoggerSeriousness& seriousness, const std::string& format) {
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
            printf("%s %s \n", _loggerFormat.c_str(), format.c_str());
        } else if(seriousness == LoggerSeriousness::Info) {
            _loggerFormat = "[ Time: " + std::to_string(_now->tm_hour) + ":" + std::to_string(_now->tm_min) + ":" + _seconds + " ] [ Type: INFO ]";
            printf("%s %s \n", _loggerFormat.c_str(), format.c_str());
        } else if(seriousness == LoggerSeriousness::Warning) {
            _loggerFormat = "[ Time: " + std::to_string(_now->tm_hour) + ":" + std::to_string(_now->tm_min) + ":" + _seconds + " ] [ Type: WARNING ]";
            printf("%s %s \n", _loggerFormat.c_str(), format.c_str());
        } else if(seriousness == LoggerSeriousness::Error) {
            _loggerFormat = "[ Time: " + std::to_string(_now->tm_hour) + ":" + std::to_string(_now->tm_min) + ":" + _seconds + " ] [ Type: ERROR ]";
            printf("%s %s \n", _loggerFormat.c_str(), format.c_str());
        } else if(seriousness == LoggerSeriousness::Critical) {
            _loggerFormat = "[ Time: " + std::to_string(_now->tm_hour) + ":" + std::to_string(_now->tm_min) + ":" + _seconds + " ] [ Type: CRITICAL ]";
            printf("%s %s \n", _loggerFormat.c_str(), format.c_str());
        }
    }

    void Logger::Endl() {
        printf("\n");
        hk::AsColor(hk::Color::Reset);
    }
};
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
};
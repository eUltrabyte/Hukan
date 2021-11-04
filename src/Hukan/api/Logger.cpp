#include "Logger.hpp"

namespace hk {
    Logger::Logger(const LoggerSeriousness& seriousness, const std::string& format, Terminal::ColorList color) {
        Log(seriousness, format, color);
    }
    
    Logger::~Logger() {
        delete this;
    }

    void Logger::Log(const LoggerSeriousness& seriousness, const std::string& format, Terminal::ColorList color) {
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
            Terminal::Color::UseColor(Terminal::ColorList::Green);
            printf("%s ", _timeFormat.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::Reset);
            printf("%s ", _loggerFormat.c_str());
            Terminal::Color::UseColor(color);
            printf("%s \n", format.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::Reset);
        } else if(seriousness == LoggerSeriousness::Info) {
            _timeFormat = "[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ]";
            _loggerFormat = "[ Type: Info ]";
            Terminal::Color::UseColor(Terminal::ColorList::Green);
            printf("%s ", _timeFormat.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::Cyan);
            printf("%s ", _loggerFormat.c_str());
            Terminal::Color::UseColor(color);
            printf("%s \n", format.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::Reset);
        } else if(seriousness == LoggerSeriousness::Warning) {
            _timeFormat = "[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ]";
            _loggerFormat = "[ Type: Warning ]";
            Terminal::Color::UseColor(Terminal::ColorList::Green);
            printf("%s ", _timeFormat.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::DarkMagenta);
            printf("%s ", _loggerFormat.c_str());
            Terminal::Color::UseColor(color);
            printf("%s \n", format.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::Reset);
        } else if(seriousness == LoggerSeriousness::Error) {
            _timeFormat = "[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ]";
            _loggerFormat = "[ Type: Error ]";
            Terminal::Color::UseColor(Terminal::ColorList::Green);
            printf("%s ", _timeFormat.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::Red);
            printf("%s ", _loggerFormat.c_str());
            Terminal::Color::UseColor(color);
            printf("%s \n", format.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::Reset);
        } else if(seriousness == LoggerSeriousness::Critical) {
            _timeFormat = "[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ]";
            _loggerFormat = "[ Type: Critical ]";
            Terminal::Color::UseColor(Terminal::ColorList::Green);
            printf("%s ", _timeFormat.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::DarkRed);
            printf("%s ", _loggerFormat.c_str());
            Terminal::Color::UseColor(color);
            printf("%s \n", format.c_str());
            Terminal::Color::UseColor(Terminal::ColorList::Reset);
        }
    }

    void Logger::Endl() {
        printf("\n");
        Terminal::Color::UseColor(Terminal::ColorList::Reset);
    }
};
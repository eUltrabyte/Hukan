#include "Logger.hpp"

namespace hk {
    Logger::Logger(std::string_view filename) {
        // TODO: writing to file
    }

    void Logger::Log(std::string_view format, Terminal::ColorList color) {
        Terminal::Color::UseColor(color);
        printf("%s", format.data());
    }

    void Logger::Log(const LoggerSeriousness& seriousness, std::string_view format, Terminal::ColorList color) {
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

        if(seriousness == LoggerSeriousness::Undefined) {
            Log(std::string("[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ] "), Terminal::ColorList::Green);
            Log(std::string("[ Type: Undefined ] "), Terminal::ColorList::Reset);
            Log(format, color);
            Endl();
        } else if(seriousness == LoggerSeriousness::Info) {
            Log(std::string("[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ] "), Terminal::ColorList::Green);
            Log(std::string("[ Type: Info ] "), Terminal::ColorList::Cyan);
            Log(format, color);
            Endl();
        } else if(seriousness == LoggerSeriousness::Warning) {
            Log(std::string("[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ] "), Terminal::ColorList::Green);
            Log(std::string("[ Type: Warning ] "), Terminal::ColorList::DarkMagenta);
            Log(format, color);
            Endl();
        } else if(seriousness == LoggerSeriousness::Error) {
            Log(std::string("[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ] "), Terminal::ColorList::Green);
            Log(std::string("[ Type: Error ] "), Terminal::ColorList::Red);
            Log(format, color);
            Endl();
        } else if(seriousness == LoggerSeriousness::Critical) {
            Log(std::string("[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ] "), Terminal::ColorList::Green);
            Log(std::string("[ Type: Critical ] "), Terminal::ColorList::DarkRed);
            Log(format, color);
            Endl();
        } else {
            Log(std::string("[ Time: " + _hours + ":" + _minutes + ":" + _seconds + " ] "), Terminal::ColorList::Green);
            Log(std::string("[ Type: Undefined ] "), Terminal::ColorList::Reset);
            Log(format, color);
            Endl();
        }
    }

    void Logger::Endl() {
        Log("\n", Terminal::ColorList::Reset);
    }
};
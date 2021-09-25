#include "Logger.hpp"

namespace hk {
    Logger::Logger(const LoggerSeriousness& seriousness, const std::string& format) {
        Log(seriousness, format);
    }
    
    Logger::~Logger() {
        delete this;
    }

    void Logger::Log(const LoggerSeriousness& seriousness, const std::string& format) {
        const Char_t* _loggerFormat;
        if(seriousness == LoggerSeriousness::None) {
            _loggerFormat = "[Time: TODO] [Type: NONE]";
        } else if(seriousness == LoggerSeriousness::Info) {
            _loggerFormat = "[Time: TODO] [Type: INFO]";
        } else if(seriousness == LoggerSeriousness::Warning) {
            _loggerFormat = "[Time: TODO] [Type: WARNING]";
        } else if(seriousness == LoggerSeriousness::Error) {
            _loggerFormat = "[Time: TODO] [Type: ERROR]";
        } else if(seriousness == LoggerSeriousness::Critical) {
            _loggerFormat = "[Time: TODO] [Type: CRITICAL]";
        }
        printf("%s %s \n", _loggerFormat, format.c_str());
    }

    void Logger::Endl() {
        printf("\n");
    }
};
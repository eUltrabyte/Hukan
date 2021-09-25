#pragma once

#include "../Hukan.hpp"

namespace hk {
    enum class LoggerSeriousness {
        None = Bit(0),
        Info = Bit(1),
        Warning = Bit(2),
        Error = Bit(3),
        Critical = Bit(4)
    };

    class Logger {
    public:
        Logger(const LoggerSeriousness& seriousness, const std::string& format);
        virtual ~Logger();

        static void Log(const LoggerSeriousness& seriousness, const std::string& format);

    };
};
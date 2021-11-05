#pragma once

#include "../Hukan.hpp"

namespace hk {
    enum HK_API LoggerSeriousness {
        Undefined = Bit(0),
        Info,
        Warning,
        Error,
        Critical
    };

    class HK_API Logger {
    public:
        Logger(const std::string& filename);
        virtual ~Logger();
        
        static void HK_API Log(const std::string& format, Terminal::ColorList color = Terminal::ColorList::Reset);
        static void HK_API Log(const LoggerSeriousness& seriousness, const std::string& format, Terminal::ColorList color = Terminal::ColorList::Reset);
        static void HK_API Endl();
        
    };
};
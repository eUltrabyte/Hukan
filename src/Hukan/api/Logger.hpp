#pragma once

#include "../core/Core.hpp"

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
        Logger(std::string_view filename);
        virtual ~Logger() = default;
        
        static void HK_API Log(std::string_view format, Terminal::ColorList color = Terminal::ColorList::Reset);
        static void HK_API Log(const LoggerSeriousness& seriousness, std::string_view format, Terminal::ColorList color = Terminal::ColorList::Reset);
        static void HK_API Endl();
        
    };
};
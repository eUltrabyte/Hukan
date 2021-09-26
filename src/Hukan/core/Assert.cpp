#include "Assert.hpp"

namespace hk {
    void Debugbreak(Uint_t line, const Char_t* filename) {
        std::string _format = "Breakpoint in file: " + std::string(filename) + " at line: " + std::to_string(line);
        Logger::Log(LoggerSeriousness::Warning, _format);
        std::cin.get();
    }

    void Assert() {
        Logger::Log(LoggerSeriousness::Critical, "Assertion failed");
    }
};
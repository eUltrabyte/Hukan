#include "Assert.hpp"

namespace hk {
    void Assert() {
        Logger::Log(LoggerSeriousness::Critical, "Assertion failed");
        std::cin.get();
    }
};
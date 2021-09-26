#include <Hukan/Hukan.hpp>

void Timer() {
    while(true) {
        hk::Logger::Log(hk::LoggerSeriousness::None, "Timer");
    }
}

int main(int argc, char** argv) {
    for(int i = 0; i <= 4; ++i) {
        hk::Logger::Log(hk::LoggerSeriousness(hk::Bit(i)), "Test");
    }

    hk::Logger::Endl();

    for(int i = 0; i <= 14; ++i) {
        hk::Logger::Log(hk::LoggerSeriousness::None, "Test", hk::Bit(i));
    }

    hk::Logger::Endl();

    // std::async(std::launch::async, Timer);

    std::cin.get();
    return 0;
}
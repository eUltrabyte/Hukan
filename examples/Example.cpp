#include <Hukan/Hukan.hpp>
#include <iostream>

int main(int argc, char** argv) {
    for(int i = 0; i < 5; ++i) {
        hk::Logger::Log(hk::LoggerSeriousness(hk::Bit(i)), "Test");
    }

    hk::Logger::Endl();

    for(int i = 0; i <= 14; ++i) {
        hk::AsColor(hk::Color(hk::Bit(i)));
        hk::Logger::Log(hk::LoggerSeriousness::None, "Test");
    }

    hk::Logger::Endl();

    std::cin.get();
    return 0;
}
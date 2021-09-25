#include <Hukan/Hukan.hpp>
#include <iostream>

int main(int argc, char** argv) {
    for(int i = 0; i < 5; ++i) {
        hk::Logger::Log(hk::LoggerSeriousness(hk::Bit(i)), "Test");
    }

    hk::AsColor(hk::Color::Reset);
    hk::AsColor(hk::Color::Red);

    std::cin.get();
    return 0;
}
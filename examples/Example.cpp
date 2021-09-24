#include <Hukan/Hukan.hpp>
#include <iostream>

int main(int argc, char** argv) {
    hk::Logger::Log(hk::LoggerSeriousness::None, hk::String_t("Test"));
    
    std::cout << hk::Terminal::AsColor(hk::Color::Red) << "\n";
    std::cout << hk::AsColor(hk::Color::Red) << "\n";

    std::cin.get();
    return 0;
}
#include "../Terminal.hpp"

#if defined(_WIN32)
namespace hk {
    extern Int_t Win32AsColor(Color color);
};
#endif
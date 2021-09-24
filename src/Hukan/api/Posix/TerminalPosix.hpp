#include "../Terminal.hpp"

#if defined(__unix__)
namespace hk {
    extern Int_t PosixAsColor(Color color);
};
#endif
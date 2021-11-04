#pragma once

#include "../../Hukan.hpp"

namespace hk {
    class HK_API Surface {
    public:
        Surface();
        virtual ~Surface();

        virtual void Create();
        virtual void Destroy();

        virtual void SetVkInstance(VkInstance* pVkInstance = nullptr);

        HK_NODISCARD virtual VkInstance* GetVkInstance() HK_NOEXCEPT;
    
    private:
        VkInstance* mpVkInstance;

    };
};

#if defined(HUKAN_SYSTEM_WIN32)
    #include "Win32/SurfaceWin32.hpp"
#elif defined(HUKAN_SYSTEM_POSIX)
    // TODO for Posix
#endif
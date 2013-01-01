#ifndef WIN32_IIDPPVARGSHELPER_H
#define WIN32_IIDPPVARGSHELPER_H

#include "unknwn.h"

extern "C++"
{
    template<typename T> void** IID_PPV_ARGS_Helper(T** pp)
    {
        static_cast<IUnknown*>(*pp);    // make sure everyone derives from IUnknown
        return reinterpret_cast<void**>(pp);
    }
}

#endif // WIN32_IIDPPVARGSHELPER_H

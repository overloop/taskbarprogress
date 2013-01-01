#ifndef WIN32_CHANGEWINDOWMESSAGEFILTER_H
#define WIN32_CHANGEWINDOWMESSAGEFILTER_H

#include "winuser.h"
#include "windef.h"

#define __in
#define MSGFLT_ADD 1
#define MSGFLT_REMOVE 2

extern "C" {
WINUSERAPI
BOOL
WINAPI
ChangeWindowMessageFilter(
    __in UINT message,
    __in DWORD dwFlag);

}

#endif // WIN32_CHANGEWINDOWMESSAGEFILTER_H

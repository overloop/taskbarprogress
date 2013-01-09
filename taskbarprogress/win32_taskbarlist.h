#ifndef WIN32_TASKBARLIST_H
#define WIN32_TASKBARLIST_H

#include "objbase.h"
#include "windows.h"
#include "win32_tbpflag.h"

#define __RPC__in
#define __RPC__in_ecount_full(x)
#define __RPC__in_opt
#define __RPC__in_opt_string
#define __in

typedef IUnknown *HIMAGELIST;
typedef struct THUMBBUTTON *LPTHUMBBUTTON;

static const CLSID CLSID_TaskbarList = {0x56FDF344,0xFD6D,0x11d0,{0x95,0x8A,0x00,0x60,0x97,0xC9,0xA0,0x90}};

//EXTERN_C const IID IID_ITaskbarList;
//EXTERN_C const IID IID_ITaskbarList2;
//EXTERN_C const IID IID_ITaskbarList3;

static const IID IID_ITaskbarList3 = {0xea1afb91,0x9e28,0x4b86,{0x90,0xe9,0x9e,0x9f,0x8a,0x5e,0xef,0xaf}};

typedef interface ITaskbarList ITaskbarList;
typedef interface ITaskbarList2 ITaskbarList2;
typedef interface ITaskbarList3 ITaskbarList3;

MIDL_INTERFACE("56FDF342-FD6D-11d0-958A-006097C9A090")
ITaskbarList : public IUnknown
{
    public:
    virtual HRESULT STDMETHODCALLTYPE HrInit( void) = 0;

    virtual HRESULT STDMETHODCALLTYPE AddTab(
                /* [in] */ __RPC__in HWND hwnd) = 0;

    virtual HRESULT STDMETHODCALLTYPE DeleteTab(
                /* [in] */ __RPC__in HWND hwnd) = 0;

    virtual HRESULT STDMETHODCALLTYPE ActivateTab(
                /* [in] */ __RPC__in HWND hwnd) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetActiveAlt(
                /* [in] */ __RPC__in HWND hwnd) = 0;

};

MIDL_INTERFACE("602D4995-B13A-429b-A66E-1935E44F4317")
ITaskbarList2 : public ITaskbarList
{
    public:
    virtual HRESULT STDMETHODCALLTYPE MarkFullscreenWindow(
                /* [in] */ __RPC__in HWND hwnd,
                /* [in] */ BOOL fFullscreen) = 0;

};

MIDL_INTERFACE("ea1afb91-9e28-4b86-90e9-9e9f8a5eefaf")
ITaskbarList3 : public ITaskbarList2
{
    public:
    virtual HRESULT STDMETHODCALLTYPE SetProgressValue(
                /* [in] */ __RPC__in HWND hwnd,
                /* [in] */ ULONGLONG ullCompleted,
                /* [in] */ ULONGLONG ullTotal) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetProgressState(
                /* [in] */ __RPC__in HWND hwnd,
                /* [in] */ TBPFLAG tbpFlags) = 0;

    virtual HRESULT STDMETHODCALLTYPE RegisterTab(
                /* [in] */ __RPC__in HWND hwndTab,
                /* [in] */ __RPC__in HWND hwndMDI) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnregisterTab(
                /* [in] */ __RPC__in HWND hwndTab) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetTabOrder(
                /* [in] */ __RPC__in HWND hwndTab,
                /* [in] */ __RPC__in HWND hwndInsertBefore) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetTabActive(
                /* [in] */ __RPC__in HWND hwndTab,
                /* [in] */ __RPC__in HWND hwndMDI,
                /* [in] */ DWORD dwReserved) = 0;

    virtual HRESULT STDMETHODCALLTYPE ThumbBarAddButtons(
                /* [in] */ __RPC__in HWND hwnd,
                /* [in] */ UINT cButtons,
                /* [size_is][in] */ __RPC__in_ecount_full(cButtons) LPTHUMBBUTTON pButton) = 0;

    virtual HRESULT STDMETHODCALLTYPE ThumbBarUpdateButtons(
                /* [in] */ __RPC__in HWND hwnd,
                /* [in] */ UINT cButtons,
                /* [size_is][in] */ __RPC__in_ecount_full(cButtons) LPTHUMBBUTTON pButton) = 0;

    virtual HRESULT STDMETHODCALLTYPE ThumbBarSetImageList(
                /* [in] */ __RPC__in HWND hwnd,
                /* [in] */ __RPC__in_opt HIMAGELIST himl) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetOverlayIcon(
                /* [in] */ __RPC__in HWND hwnd,
                /* [in] */ __RPC__in HICON hIcon,
                /* [string][unique][in] */ __RPC__in_opt_string LPCWSTR pszDescription) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetThumbnailTooltip(
                /* [in] */ __RPC__in HWND hwnd,
                /* [string][unique][in] */ __RPC__in_opt_string LPCWSTR pszTip) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetThumbnailClip(
                /* [in] */ __RPC__in HWND hwnd,
                /* [in] */ __RPC__in RECT *prcClip) = 0;

};


#endif // WIN32_TASKBARLIST_H

/*
 * qtaskbarlist3.cpp
 *
 * Copyright (c) 2009 Akaiten <akaiten at mail.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "qtaskbarlist3.h"
#include "win32_changewindowmessagefilter.h"
#include <QDebug>

//-----------------------------------------------------------------------------
// QTaskbarList3
//-----------------------------------------------------------------------------

QTaskbarList3 *QTaskbarList3::m_instance = NULL;

QTaskbarList3::QTaskbarList3() :
	QWidget(NULL, Qt::Window), m_pTaskbarList(NULL)
{
    CoInitialize(0);

	// Register "TaskbarButtonCreated" message
	wm_TaskbarButtonCreated = RegisterWindowMessage(L"TaskbarButtonCreated");
	// In case the application is run elevated, allow the
	// TaskbarButtonCreated message through.

#if (WINVER >= 0x600)
    ChangeWindowMessageFilter(wm_TaskbarButtonCreated, MSGFLT_ADD);
#endif
	// Foreced create hidden window
	winId();

	// Get ITaskbarList3 interface
	getInterface();

}

QTaskbarList3 * QTaskbarList3::instance()
{
	if (!m_instance)
		m_instance = new QTaskbarList3();

	return m_instance;
}

QTaskbarList3::~QTaskbarList3()
{
	if (m_pTaskbarList)
		m_pTaskbarList->Release();

	m_instance = NULL;

    CoUninitialize();
}

bool QTaskbarList3::winEvent(MSG *message, long *result)
{
	if (message->message == wm_TaskbarButtonCreated)
	{
		getInterface();
		return true;
	}
	return QWidget::winEvent(message, result);
}

void QTaskbarList3::getInterface()
{
	if (!m_pTaskbarList)
	{
        HRESULT hr = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3,(LPVOID*) &m_pTaskbarList);
		if (SUCCEEDED(hr))
		{
			hr = m_pTaskbarList->HrInit();
			if (FAILED(hr))
			{
				m_pTaskbarList->Release();
				m_pTaskbarList = NULL;
			}
        } else {
            switch (hr)
            {
            case REGDB_E_CLASSNOTREG:
                qDebug() << "A specified class (TaskbarList) is not registered in the registration database.";
                break;
            case CLASS_E_NOAGGREGATION:
                qDebug() << "This class cannot be created as part of an aggregate.";
                break;
            case E_NOINTERFACE:
                qDebug() << "The specified class does not implement the requested interface, or the controlling IUnknown does not expose the requested interface.";
                break;
            case E_POINTER:
                qDebug() << "The ppv parameter is NULL.";
                break;
            }
            m_pTaskbarList = 0;
        }
	}
}

//qt-creator-2.6.1-src\src\plugins\coreplugin\progressmanager\progressmanager_win.cpp
#if QT_VERSION >= 0x050000
Q_GUI_EXPORT HICON qt_pixmapToWinHICON(const QPixmap &p);

static inline QWindow *windowOfWidget(const QWidget *widget)
{
    if (QWindow *window = widget->windowHandle())
        return window;
    if (QWidget *topLevel = widget->nativeParentWidget())
        return topLevel->windowHandle();
    return 0;
}

static inline HWND hwndOfWidget(const QWidget *w)
{
    void *result = 0;
    if (QWindow *window = windowOfWidget(w))
        result = QGuiApplication::platformNativeInterface()->nativeResourceForWindow("handle", window);
    return static_cast<HWND>(result);
}
#else
static inline HWND hwndOfWidget(const QWidget *w)
{
    return w->winId();
}
#endif

HRESULT QTaskbarList3::setProgressState(QWidget *widget, TBPFLAG tbpFlags) const
{
	return m_pTaskbarList ?
        m_pTaskbarList->SetProgressState(hwndOfWidget(widget), tbpFlags) : E_NOTIMPL;
}

HRESULT QTaskbarList3::setProgressValue(QWidget *widget, quint64 ullCompleted, quint64 ullTotal) const
{
	return m_pTaskbarList ?
        m_pTaskbarList->SetProgressValue(hwndOfWidget(widget), ullCompleted, ullTotal) : E_NOTIMPL;
}

#if QT_VERSION < 0x040600
HICON createIcon(const QPixmap &icon)
{
	QImage mask =
		icon.mask().toImage().convertToFormat(QImage::Format_Mono);
	if (mask.isNull())
	{
		mask = QImage(icon.size(), QImage::Format_Mono);
		mask.fill(Qt::color1);
	}

    int w = mask.width();
    int h = mask.height();
    int bpl = ((w+15)/16)*2;                        // bytesPerLine, 16 bit alignment
    uchar *bits = new uchar[bpl*h];
    mask.invertPixels();
    for (int y=0; y<h; y++)
        memcpy(bits+y*bpl, mask.scanLine(y), bpl);
    HBITMAP hbm = CreateBitmap(w, h, 1, 1, bits);
    delete [] bits; 

    ICONINFO ii;
    ii.fIcon    = true;
    ii.hbmMask  = hbm;
	ii.hbmColor = icon.toWinHBITMAP(QPixmap::Alpha);
    ii.xHotspot = 0;
    ii.yHotspot = 0;
	HICON result = CreateIconIndirect(&ii);

    DeleteObject(ii.hbmColor);
    DeleteObject(hbm);
	return result;
}
#endif

HRESULT QTaskbarList3::setOverlayIcon(QWidget *widget,
	const QPixmap &overlay, const QString &alt)
{
	if (m_pTaskbarList)
	{
#if QT_VERSION >= 0x040600
		HICON icon = overlay.toWinHICON();
#else
		HICON icon = createIcon(overlay);
#endif
        HRESULT ret = m_pTaskbarList->SetOverlayIcon(hwndOfWidget(widget), icon, reinterpret_cast<LPCWSTR>(alt.utf16()));
		DestroyIcon(icon);
		return ret;
	}
	return E_NOTIMPL;
}

HRESULT QTaskbarList3::setOverlayIcon(QWidget *widget,
		HICON icon, const QString &alt)
{
	return m_pTaskbarList ?
        m_pTaskbarList->SetOverlayIcon(hwndOfWidget(widget), icon, reinterpret_cast<LPCWSTR>(alt.utf16())) : E_NOTIMPL;
}

HRESULT QTaskbarList3::addTab(QWidget *widget)
{
	return (m_pTaskbarList && widget) ?
        m_pTaskbarList->AddTab(hwndOfWidget(widget)) : E_NOTIMPL;
}

HRESULT QTaskbarList3::deleteTab(QWidget *widget)
{
	return (m_pTaskbarList && widget) ?
        m_pTaskbarList->DeleteTab(hwndOfWidget(widget)) : E_NOTIMPL;
}

HRESULT QTaskbarList3::activateTab(QWidget *widget)
{
	return (m_pTaskbarList && widget) ?
        m_pTaskbarList->ActivateTab(hwndOfWidget(widget)) : E_NOTIMPL;
}

HRESULT QTaskbarList3::setActiveAlt(QWidget *widget)
{
	return (m_pTaskbarList && widget) ?
        m_pTaskbarList->SetActiveAlt(hwndOfWidget(widget)) : E_NOTIMPL;
}

HRESULT QTaskbarList3::registerTab(QWidget *tab, QWidget *mainWindow)
{
	return (m_pTaskbarList && tab && mainWindow) ?
        m_pTaskbarList->RegisterTab(hwndOfWidget(tab), hwndOfWidget(mainWindow)) : E_NOTIMPL;
}

HRESULT QTaskbarList3::unregisterTab(QWidget *tab)
{
	return (m_pTaskbarList && tab) ?
        m_pTaskbarList->UnregisterTab(hwndOfWidget(tab)) : E_NOTIMPL;
}

HRESULT QTaskbarList3::setTabOrder(QWidget *tab, QWidget *insertBefore)
{
	return (m_pTaskbarList && tab && insertBefore) ?
        m_pTaskbarList->SetTabOrder(hwndOfWidget(tab), hwndOfWidget(insertBefore)) : E_NOTIMPL;
}

/*
 *  qtaskbarlist3.h
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

#ifndef QTASKBARLIST3_H
#define QTASKBARLIST3_H

#include <QWidget>
#include "win32_taskbarlist.h"

#ifndef HRESULT
typedef long HRESULT;
#endif

class QTaskbarList3 : public QWidget
{
	Q_OBJECT

protected:
	QTaskbarList3();

public:
	~QTaskbarList3();
	static QTaskbarList3 * instance();

	HRESULT addTab(QWidget *widget);
	HRESULT deleteTab(QWidget *widget);
	HRESULT activateTab(QWidget *widget);
	HRESULT setActiveAlt(QWidget *widget);

	HRESULT registerTab(QWidget *tab, QWidget *mainWindow);
	HRESULT unregisterTab(QWidget *tab);
	HRESULT setTabOrder(QWidget *tab, QWidget *insertBefore);

	HRESULT setProgressState(QWidget *widget, TBPFLAG tbpFlags) const;
	HRESULT setProgressValue(QWidget *widget, quint64 ullCompleted, quint64 ullTotal) const;

	HRESULT setOverlayIcon(QWidget *widget,
		const QPixmap &overlay, const QString &alt);
	HRESULT setOverlayIcon(QWidget *widget,
		HICON icon, const QString &alt);

protected:
	bool winEvent(MSG *message, long *result);

private:
	void getInterface();

private:
	static QTaskbarList3 *m_instance;
	ITaskbarList3 *m_pTaskbarList;
	UINT wm_TaskbarButtonCreated;
};

#endif // QTASKBARLIST3_H

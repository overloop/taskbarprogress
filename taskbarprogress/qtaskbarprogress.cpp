/*
 * qtaskbarprogress.cpp
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

#include <QtGlobal>
#include <QWidget>
#include "qtaskbarprogress.h"

#ifdef Q_OS_WIN
#include "qtaskbarlist3.h"
#endif

//-----------------------------------------------------------------------------
// QTaskbarProgress
//-----------------------------------------------------------------------------

QTaskbarProgress::QTaskbarProgress(QWidget *parent) :
    QObject(parent), m_state(TBPF_NOPROGRESS), m_min(0), m_max(100), m_value(-1)
{

}

QTaskbarProgress::~QTaskbarProgress()
{

}

void QTaskbarProgress::reset()
{
#ifdef Q_OS_WIN
	QTaskbarList3::instance()->setProgressState(
		reinterpret_cast<QWidget *>(parent()), TBPF_NOPROGRESS);

	m_value = m_min - 1;
	if (m_min == INT_MIN)
		m_value = INT_MIN;
#endif
}

void QTaskbarProgress::setMaximum(int maximum)
{
    setRange(qMin(m_min, maximum), maximum); 
}

void QTaskbarProgress::setMinimum(int minimum)
{
    setRange(minimum, qMax(m_max, minimum)); 
}

void QTaskbarProgress::setRange(int minimum, int maximum)
{
	m_min = minimum;
	m_max = qMax(minimum, maximum);
	if (m_value < (m_min - 1) || m_value > m_max)
		reset();
}

void QTaskbarProgress::setValue(int value)
{
	if (m_value == value ||
		((value > m_max || value < m_min) &&
			(m_max != 0 || m_min != 0)))
		return;
	m_value = value;
	emit valueChanged(value);

	update(); 
}

void QTaskbarProgress::update()
{
#ifdef Q_OS_WIN
    if (m_value == m_min)
        QTaskbarList3::instance()->setProgressState(
                    reinterpret_cast<QWidget *>(parent()), TBPF_NOPROGRESS);
    else
        QTaskbarList3::instance()->setProgressValue(
                    reinterpret_cast<QWidget *>(parent()), m_value - m_min, m_max - m_min + 1);
#endif
}

void QTaskbarProgress::setState(TBPFLAG state)
{
#ifdef Q_OS_WIN
	m_state = state;
	QTaskbarList3::instance()->setProgressState(
		reinterpret_cast<QWidget *>(parent()), m_state);
#else
    Q_UNUSED(state)
#endif
}

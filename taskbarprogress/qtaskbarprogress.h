/*
 * qtaskbarprogress.h
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

#ifndef QTASKBARPROGRESS_H
#define QTASKBARPROGRESS_H

#include <QObject>
#include "win32_tbpflag.h"

class QTaskbarProgress : public QObject
{
	Q_OBJECT

public:
	QTaskbarProgress(QWidget *parent);
	~QTaskbarProgress();
	int value() const { return m_value; }
	int maximum () const { return m_max; }
	int minimum () const { return m_min; }
	void setState(TBPFLAG state);
	TBPFLAG state() const { return m_state; }

private:
	void update();

private:
	TBPFLAG m_state;
	int m_min, m_max, m_value;

public slots:
	void reset();
	void setMaximum(int maximum);
	void setMinimum(int minimum);
	void setRange(int minimum, int maximum);
	void setValue(int value);

signals:
	void valueChanged(int value);
};

#endif // QTASKBARPROGRESS_H

#include "qtasksyncedprogressbar.h"

#include "qtaskbarprogress.h"

QTasksyncedProgressBar::QTasksyncedProgressBar(QWidget *parent) :
    QProgressBar(parent)
{
    m_taskbarProgress = new QTaskbarProgress(parent);
    connect(this,SIGNAL(valueChanged(int)),m_taskbarProgress,SLOT(setValue(int)));
}

QTaskbarProgress* QTasksyncedProgressBar::taskbarProgress()
{
    return m_taskbarProgress;
}

void QTasksyncedProgressBar::setMinimum(int minimum)
{
    QProgressBar::setMinimum(minimum);
    m_taskbarProgress->setMinimum(minimum);
}

void QTasksyncedProgressBar::setMaximum(int maximum)
{
    QProgressBar::setMaximum(maximum);
    m_taskbarProgress->setMaximum(maximum);
}

void QTasksyncedProgressBar::setRange(int minimum, int maximum)
{
    QProgressBar::setRange(minimum,maximum);
    m_taskbarProgress->setRange(minimum,maximum);

    if (minimum == maximum)
        m_taskbarProgress->setState(TBPF_INDETERMINATE);
    else
        m_taskbarProgress->setState(TBPF_NORMAL);
}

void QTasksyncedProgressBar::reset()
{
    QProgressBar::reset();
    m_taskbarProgress->reset();
}

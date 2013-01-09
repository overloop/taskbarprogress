#ifndef QTASKSYNCEDPROGRESSBAR_H
#define QTASKSYNCEDPROGRESSBAR_H

#include <QProgressBar>

class QTaskbarProgress;

/**
 * @brief The QTasksyncedProgressBar class
 * @warning Parent must be window, set it in constructor or in taskbarProgress()->setParent(QObject* parent)
 * slots are not virtual (do not use base pointer)
 */
class QTasksyncedProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit QTasksyncedProgressBar(QWidget *parent = 0);
    void setParent(QWidget *parent);
    
    QTaskbarProgress* taskbarProgress();

private:
    QTaskbarProgress* m_taskbarProgress;

signals:
    
public slots:
    /* How come these slots are not virtual in QProgressBar? I'm so pissed, it ruins my day.*/
    void setMinimum(int minimum);
    void setMaximum(int maximum);
    void setRange(int minimum, int maximum);
    void reset();
};

#endif // QTASKSYNCEDPROGRESSBAR_H

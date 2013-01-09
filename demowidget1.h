#ifndef DEMOWIDGET1_H
#define DEMOWIDGET1_H

#include <QWidget>

namespace Ui {
	class DemoWidget1;
}

class MainWindow;
class QTaskbarProgress;

/**
 * @brief The DemoWidget1 class shows how to use QTaskbarProgress
 */
class DemoWidget1 : public QWidget
{
	Q_OBJECT

public:
    DemoWidget1(QWidget *parent = 0);
    ~DemoWidget1();

protected:


private:
	Ui::DemoWidget1* ui;
	QTaskbarProgress *m_taskbarProgress;
	QTimer *timer;

private slots:
	void ontimer();
	void on_start_clicked();
	void on_indeterminate_clicked();
	void on_reset_clicked();
	void on_pause_clicked();
	void on_error_clicked();
};

#endif // DEMOWIDGET1_H

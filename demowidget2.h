#ifndef DEMOWIDGET2_H
#define DEMOWIDGET2_H

#include <QWidget>

namespace Ui {
	class DemoWidget2;
}

class DemoWidget2 : public QWidget
{
	Q_OBJECT

public:
    DemoWidget2(QWidget *parent = 0);
    ~DemoWidget2();

protected:


private:
	Ui::DemoWidget2* ui;
	QTimer *timer;

private slots:
	void ontimer();
	void on_start_clicked();
	void on_indeterminate_clicked();
	void on_reset_clicked();
	void on_pause_clicked();
	void on_error_clicked();
};

#endif // DEMOWIDGET2_H

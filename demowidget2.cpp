#include "demowidget2.h"
#include "ui_demowidget2.h"

#include "qtaskbarprogress.h"
#include <QTimer>

DemoWidget2::DemoWidget2(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DemoWidget2)
{
	ui->setupUi(this);
    //ui->progressBar->setAttribute(Qt::WA_NativeWindow);

    ui->progressBar->setRange(0, 100);

	timer = new QTimer(this);
	timer->setInterval(100);
	connect(timer, SIGNAL(timeout()), this, SLOT(ontimer()));
}

DemoWidget2::~DemoWidget2()
{
	delete ui;
}

void DemoWidget2::ontimer()
{
    int value = ui->progressBar->value() + 1;
    if (value > ui->progressBar->maximum())
	{
		timer->stop();
	}
    else
	{
        ui->progressBar->setValue(value);
	}
}

void DemoWidget2::on_start_clicked()
{
    ui->progressBar->setRange(0, 100);
	timer->start();
}

void DemoWidget2::on_indeterminate_clicked()
{
	timer->stop();
    ui->progressBar->setRange(0, 0);
}

void DemoWidget2::on_reset_clicked()
{
	timer->stop();
    ui->progressBar->reset();
    ui->progressBar->setRange(0, 100);
}

void DemoWidget2::on_pause_clicked()
{
	timer->stop();
    ui->progressBar->taskbarProgress()->setState(TBPF_PAUSED);
}

void DemoWidget2::on_error_clicked()
{
	timer->stop();
    ui->progressBar->taskbarProgress()->setState(TBPF_ERROR);
}

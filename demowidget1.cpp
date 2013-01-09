#include "demowidget1.h"
#include "ui_demowidget1.h"

#include "qtaskbarprogress.h"
#include <QTimer>

DemoWidget1::DemoWidget1(QWidget *parent) :
	QWidget(parent),
    ui(new Ui::DemoWidget1)
{
	ui->setupUi(this);
	ui->progressBar->setAttribute(Qt::WA_NativeWindow);
	
	m_taskbarProgress = new QTaskbarProgress(this);
	m_taskbarProgress->setRange(0, 100);
	connect(m_taskbarProgress, SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));

	timer = new QTimer(this);
	timer->setInterval(100);
	connect(timer, SIGNAL(timeout()), this, SLOT(ontimer()));
}

DemoWidget1::~DemoWidget1()
{
	delete ui;
}

void DemoWidget1::ontimer()
{
	int value = m_taskbarProgress->value() + 1;
	if (value > m_taskbarProgress->maximum())
	{
		timer->stop();
	}
	else
	{
		m_taskbarProgress->setValue(value);
	}
}

void DemoWidget1::on_start_clicked()
{
	m_taskbarProgress->setState(TBPF_NORMAL);
	ui->progressBar->setRange(0, 100);
	timer->start();
}

void DemoWidget1::on_indeterminate_clicked()
{
	timer->stop();
	m_taskbarProgress->setState(TBPF_INDETERMINATE);
    ui->progressBar->setRange(0, 0);
    ui->progressBar->setValue(-1);
}

void DemoWidget1::on_reset_clicked()
{
	timer->stop();
	m_taskbarProgress->reset();
	ui->progressBar->setRange(0, 100);
	ui->progressBar->reset();
}

void DemoWidget1::on_pause_clicked()
{
	timer->stop();
	m_taskbarProgress->setState(TBPF_PAUSED);
	ui->progressBar->setRange(0, 100);
}

void DemoWidget1::on_error_clicked()
{
	timer->stop();
	m_taskbarProgress->setState(TBPF_ERROR);
	ui->progressBar->setRange(0, 100);
}

#include "widget.h"
#include "ui_widget.h"

#include "taskbarprogress/qtaskbarprogress.h"

#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    timer(new QTimer(this))
{
    ui->setupUi(this);
    taskbarProgress = new QTaskbarProgress(this);
    taskbarProgress->setRange(0,100);

    timer->setInterval(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_timeout()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_button_clicked()
{
    timer->stop();
    ui->progress->setValue(0);
    taskbarProgress->reset();
    timer->start();
}

void Widget::timer_timeout()
{
    int v = ui->progress->value();
    if (v==100) return;
    v++;
    ui->progress->setValue(v);
    taskbarProgress->setValue(v);

    if (v==100)
    {
        timer->stop();
        taskbarProgress->reset();
        ui->progress->reset();
    }
}

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QTaskbarProgress;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private:
    Ui::Widget *ui;
    QTaskbarProgress* taskbarProgress;
    QTimer* timer;

private slots:
    void on_button_clicked();
    void timer_timeout();

};

#endif // WIDGET_H

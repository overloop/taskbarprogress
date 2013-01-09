#include <QApplication>

#include "demowidget1.h"
#include "demowidget2.h"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    DemoWidget1 widget1;
    widget1.show();
    DemoWidget2 widget2;
    widget2.show();

    return app.exec();
}

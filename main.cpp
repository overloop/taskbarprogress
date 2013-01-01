#include <QApplication>

#ifdef Q_OS_WIN32
#include "objbase.h"
#endif

#include "widget.h"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);

#ifdef Q_OS_WIN32
    CoInitialize(NULL);
#endif

    Widget widget;
    widget.show();

    return app.exec();
}


include (taskbarprogress/taskbarprogress.pri)

SOURCES += \
    main.cpp \
    demowidget1.cpp \
    demowidget2.cpp

HEADERS += \
    demowidget1.h \
    demowidget2.h

FORMS += \
    demowidget1.ui \
    demowidget2.ui

TARGET = qtaskbarprogress

#vista
#DEFINES += WINVER=0x600
#xp
#DEFINES += WINVER=0x501


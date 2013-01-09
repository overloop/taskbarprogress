
INCLUDEPATH += \
    taskbarprogress

HEADERS += \
    taskbarprogress/qtaskbarprogress.h \
    taskbarprogress/win32_tbpflag.h \
    taskbarprogress/qtasksyncedprogressbar.h

SOURCES += \
    taskbarprogress/qtasksyncedprogressbar.cpp \
    taskbarprogress/qtaskbarprogress.cpp

win32 {
HEADERS += \
    taskbarprogress/qtaskbarlist3.h \
    taskbarprogress/win32_taskbarlist.h \
    taskbarprogress/win32_changewindowmessagefilter.h

SOURCES += \
    taskbarprogress/qtaskbarlist3.cpp

LIBS += \
    -L"C:/windows/system32" -lole32
}

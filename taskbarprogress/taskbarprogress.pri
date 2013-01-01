

HEADERS += \
    taskbarprogress/qtaskbarprogress.h \
    taskbarprogress/win32_tbpflag.h

win32 {
HEADERS += \
    taskbarprogress/qtaskbarlist3.h \
    taskbarprogress/win32_taskbarlist.h \
    taskbarprogress/win32_changewindowmessagefilter.h \
    taskbarprogress/win32_iidppvargshelper.h

SOURCES += \
    taskbarprogress/qtaskbarprogress_win32.cpp \
    taskbarprogress/qtaskbarlist3.cpp

LIBS += \
    -L"C:/windows/system32" -lole32
}

unix {
SOURCES += \
    taskbarprogress/qtaskbarprogress_unix.cpp
}

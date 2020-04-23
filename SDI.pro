QT       += core gui testlib concurrent sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    imagedisplay.cpp \
    labels.cpp \
    fileio.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BoundingBox.h \
    imagedisplay.h \
    labels.h \
    fileio.h \
    mainwindow.h

FORMS += \
    imagedisplay.ui \
    mainwindow.ui

TRANSLATIONS += \
    SDI_en_GB.ts
unix {
    INCLUDEPATH += /usr/include/opencv4
    LIBS += -L/usr/local/lib -L/usr/include/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs
}
win32 {
    INCLUDEPATH += D:\opencv\build\include
    LIBS += D:\opencv_build\bin\libopencv_core430.dll
    LIBS += D:\opencv_build\bin\libopencv_highgui430.dll
    LIBS += D:\opencv_build\bin\libopencv_imgcodecs430.dll
    LIBS += D:\opencv_build\bin\libopencv_imgproc430.dll
    LIBS += D:\opencv_build\bin\libopencv_features2d430.dll
    LIBS += D:\opencv_build\bin\libopencv_calib3d430.dll
}
target.path = /tmp/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

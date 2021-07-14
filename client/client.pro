QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disab le deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth.cpp \
    barn.cpp \
    barndetailsdialog.cpp \
    detailsdialog.cpp \
    farm.cpp \
    farmer.cpp \
    fields.cpp \
    livingplaces.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    scoreboarddialog.cpp \
    shop.cpp \
    shopdialog.cpp \
    silo.cpp \
    tcpsocket.cpp

HEADERS += \
    auth.h \
    barn.h \
    barndetailsdialog.h \
    detailsdialog.h \
    enums.h \
    farm.h \
    farmer.h \
    fields.h \
    globals.h \
    livingplaces.h \
    loginwindow.h \
    mainwindow.h \
    place.h \
    scoreboarddialog.h \
    shop.h \
    shopdialog.h \
    silo.h \
    tcpsocket.h

FORMS += \
    barndetailsdialog.ui \
    detailsdialog.ui \
    loginwindow.ui \
    mainwindow.ui \
    scoreboarddialog.ui \
    shopdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

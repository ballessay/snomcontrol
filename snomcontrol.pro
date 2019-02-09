#-------------------------------------------------
#
# Project created by QtCreator 2019-02-09T16:42:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snomcontrol
TEMPLATE = app

# The following define makes your compiler emit warnings if yoCMainWindowu use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CMainWindow
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Setup SingleApplication
include(3rdparty/SingleApplication-3.0.14/singleapplication.pri)
DEFINES += QAPPLICATION_CLASS=QApplication


CONFIG += c++11

include(src/src.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons/snomcontrol.qrc

DISTFILES += \
    CODING.md \
    COPYING \
    README.md


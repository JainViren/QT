QT       += core gui svg sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SqlProject
TEMPLATE = app

SOURCES += main.cpp         application.cpp

HEADERS += application.h

FORMS += application.ui

RESOURCES += resources.qrc

unix:{
    INCLUDEPATH += /opt/crosscontrol/include

    linux-g++ { # Qt5 x86
        message(Compiling for $$QT_VERSION OS Version - Linux Virtual Machine)
        DEFINES += TARGET_X86
        LIB_PATH = /opt/crosscontrol/x86_64/vm/lib
    }

    linux-arm-none-gnueabi-g++ { # i.MX 5
        message(Compiling for $$QT_VERSION LinX Version - Linux ARM iMX5 CCpilot)
        DEFINES += LINUX
        DEFINES += CCAUX
        DEFINES += TARGET_ARM_IMX5
        LIBS += -lcc-aux2
        LIB_PATH = /opt/crosscontrol/arm/imx5/lib
    }

    linux-oe-g++ { # Qt5 VS/VI2 OS version
        message(Compiling for $$QT_VERSION OS Version - Linux ARM iMX6 CCpilot)
        DEFINES += LINUX
        DEFINES += CCAUX
        DEFINES += TARGET_ARM_IMX6
        LIBS += -lcc-aux2
        LIB_PATH = /opt/crosscontrol/arm/imx6/lib
    }

    linux-imx6-g++ { # i.MX 6
        message(Compiling for $$QT_VERSION LinX Version - Linux ARM iMX6 CCpilot)
        DEFINES += LINUX
        DEFINES += CCAUX
        DEFINES += TARGET_ARM_IMX6
        LIBS += -lcc-aux2
        LIB_PATH = /opt/crosscontrol/arm/imx6/lib
    }

    linux-imx8-g++ { # i.MX 8
        message(Compiling for Qt $$QT_VERSION LinX Version - Linux ARM iMX8 CCpilot)
        DEFINES += LINUX
        DEFINES += CCAUX
        DEFINES += TARGET_ARM_IMX8
        LIBS += -lcc-aux2
        LIB_PATH = /opt/crosscontrol/arm/imx8/lib
    }

    linux-corei7-64-g++ { # Core i7
        message(Compiling for Qt $$QT_VERSION LinX Version - Linux Core i7 x86_64 CCpilot)
        DEFINES += LINUX
        DEFINES += CCAUX
        DEFINES += TARGET_COREI7_64
        LIBS += -lcc-aux2
        LIB_PATH = /opt/crosscontrol/x86_64/corei7/lib
    }

#######################################################
# CrossControl specific libraries
# REMOVE DEPENDENCIES THAT ARE NOT USED
LIBS += -L$$LIB_PATH -lqt5cccommon
LIBS += -L$$LIB_PATH -lqt5ccverticalmeter
LIBS += -L$$LIB_PATH -lqt5cchorizontalmeter
LIBS += -L$$LIB_PATH -lqt5ccbottombar
LIBS += -L$$LIB_PATH -lqt5cccheckbox
LIBS += -L$$LIB_PATH -lqt5ccroundindicator
LIBS += -L$$LIB_PATH -lqt5ccsvgbutton
LIBS += -L$$LIB_PATH -lqt5ccnotification
LIBS += -L$$LIB_PATH -lqt5ccsvgonoffbutton
LIBS += -L$$LIB_PATH -lqt5cconoffbutton
LIBS += -L$$LIB_PATH -lqt5cctogglebutton
LIBS += -L$$LIB_PATH -lqt5ccplusminusbutton
LIBS += -L$$LIB_PATH -lqt5ccverticalgauge
LIBS += -L$$LIB_PATH -lqt5ccplusminusbuttonvertical
LIBS += -L$$LIB_PATH -lqt5ccpopupmenu
LIBS += -L$$LIB_PATH -lqt5ccpushbutton
LIBS += -L$$LIB_PATH -lqt5ccrectangularindicator
LIBS += -L$$LIB_PATH -lqt5ccmultineedlegauge
LIBS += -L$$LIB_PATH -lqt5ccroundgauge
LIBS += -L$$LIB_PATH -lqt5ccsegmentedgauge
LIBS += -L$$LIB_PATH -lqt5ccfillmeter
#######################################################

# To be able to execute the application on a remote device, it must be copied first.
# The following section defines the files that will be copied
target.path = /opt/SqlProject/
INSTALLS += target
}

QT += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Tell qmake where to find headers
INCLUDEPATH += ../include

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Transaction.cpp \
    BudgetManager.cpp

HEADERS += \
    ../include/MainWindow.h \
    ../include/Transaction.h \
    ../include/BudgetManager.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
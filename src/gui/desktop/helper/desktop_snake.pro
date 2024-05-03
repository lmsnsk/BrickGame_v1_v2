QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../../controller/controller.cpp \
    ../../brick_game/snake/snake_model.cpp

HEADERS += \
    mainwindow.h \
    ../../brick_game.h \
    ../../controller/controller.h \
    ../../brick_game/snake/snake_model.h

FORMS += \
    mainwindow.ui\

DEFINES += \
    DESKTOP \
    SNAKE

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

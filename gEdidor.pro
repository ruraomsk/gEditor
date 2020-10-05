QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graph/edge.cpp \
    graph/graph.cpp \
    graph/infoedge.cpp \
    graph/infovertex.cpp \
    graph/vertex.cpp \
    main.cpp \
    mainwindow.cpp \
    setup/setup.cpp \
    support.cpp

HEADERS += \
    graph/edge.h \
    graph/graph.h \
    graph/infoedge.h \
    graph/infovertex.h \
    graph/vertex.h \
    mainwindow.h \
    setup/setup.h \
    support.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dropAndCreate.sql \
    gEditor.ini

RESOURCES += \
    gEditor.qrc

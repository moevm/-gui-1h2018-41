#-------------------------------------------------
#
# Project created by QtCreator 2018-06-13T22:32:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Randomizer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        gui/mainwindow.cpp \
    gui/widgets/mylistwidget.cpp \
    gui/widgets/mylistwidgetitem.cpp \
    libs/jsonparser/json.cpp \
    models/types/randomitem.cpp \
    models/types/randomitemlist.cpp \
    models/repository/repository.cpp \
    models/actions/randomizer.cpp \
    models/actions/savetofile.cpp

HEADERS += \
        gui/mainwindow.h \
    gui/widgets/mylistwidget.h \
    gui/widgets/mylistwidgetitem.h \
    libs/jsonparser/json.h \
    models/types/randomitem.h \
    models/types/randomitemlist.h \
    models/repository/repository.h \
    models/actions/randomizer.h \
    models/structs.h \
    models/actions/savetofile.h

FORMS += \
        gui/mainwindow.ui

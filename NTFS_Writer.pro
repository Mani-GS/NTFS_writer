#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T12:29:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NTFS_Writer
TEMPLATE = app
VERSION = 1.3
TEMPLATE = app
CONFIG += warn_on

DESTDIR = bin
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
OBJECTS_DIR = build/o

SOURCES += main.cpp\
        mainwindow.cpp \
    manager.cpp \
    droparea.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    manager.h \
    droparea.h \
    aboutdialog.h

# Fervor autoupdater
!include("fervor/Fervor.pri") {
    error("Unable to include Fervor autoupdater.")
}


FORMS    += mainwindow.ui \
    aboutdialog.ui

LIBS += -lsqlite3

RESOURCES += \
    rescources.qrc
    
TRANSLATIONS += NTFS_Writer_it.ts
    
ICON = images/app.icns
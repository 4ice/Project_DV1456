#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T08:35:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project_DV1456
TEMPLATE = app

#Nullptr and such with g++
QMAKE_CXXFLAGS += -std=c++0x
# To include MySQL Connector/C++
LIBS += -I/usr/local/include -I/usr/local/include/cppconn -lmysqlcppconn

SOURCES += main.cpp\
        mainwindow.cpp \
    People.cpp \
    Staff.cpp \
    Competitor.cpp \
    ContestHandler.cpp \
    Track.cpp \
    TrackRecord.cpp \
    DialogDeletePerson.cpp \
    PersonNameSsn.cpp \
    DialogProgramStart.cpp \
    DialogNewContest.cpp \
    DialogDeleteTrack.cpp \
    DialogError.cpp \
    ContestNameYear.cpp \
    DialogMakeHtml.cpp

HEADERS  += mainwindow.h \
    People.h \
    Staff.h \
    Competitor.h \
    ContestHandler.h \
    Track.h \
    TrackRecord.h \
    DialogDeletePerson.h \
    PersonNameSsn.h \
    DialogProgramStart.h \
    DialogNewContest.h \
    DialogDeleteTrack.h \
    DialogError.h \
    ContestNameYear.h \
    DialogMakeHtml.h

FORMS    += mainwindow.ui \
    DialogDeletePerson.ui \
    DialogProgramStart.ui \
    DialogNewContest.ui \
    DialogDeleteTrack.ui \
    DialogMakeHtml.ui

RESOURCES +=

OTHER_FILES +=

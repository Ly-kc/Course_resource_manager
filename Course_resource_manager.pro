QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfiledialog.cpp \
    filetree.cpp \
    filterwidget.cpp \
    introwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    jsoncpp.cpp \
    datamanager.cpp \
    mypushbotton.cpp \
    noteswidget.cpp \
    recent.cpp \
    statchart.cpp \
    weblist.cpp

HEADERS += \
    QtHeaderFiles.h \
    addfiledialog.h \
    filetree.h \
    filterwidget.h \
    introwidget.h \
    mainwindow.h \
    json/json.h \
    datamanager.h \
    mypushbotton.h \
    noteswidget.h \
    recent.h \
    statchart.h \
    weblist.h

FORMS += \
    addfiledialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    static.qrc

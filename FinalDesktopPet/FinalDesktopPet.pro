QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += multimedia
CONFIG += c++11
CONFIG += resources_big


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cmp2.cpp \
    cmp3.cpp \
    entry.cpp \
    galshop.cpp \
    galsystem.cpp \
    itembox.cpp \
    itemsbox.cpp \
    main.cpp \
    mypushbutton.cpp \
    myqlabel.cpp \
    myqwitem.cpp \
    petwidget.cpp \
    role.cpp \
    timetable.cpp \
    toolbag.cpp \
    toolbag_create.cpp \
    toolbag_item.cpp

HEADERS += \
    cmp1.h \
    cmp2.h \
    cmp3.h \
    entry.h \
    galshop.h \
    galsystem.h \
    itembox.h \
    itemsbox.h \
    mypushbutton.h \
    myqlabel.h \
    myqwitem.h \
    petwidget.h \
    role.h \
    timetable.h \
    toolbag.h \
    toolbag_create.h \
    toolbag_item.h

FORMS += \
    entry.ui \
    galshop.ui \
    galsystem.ui \
    petwidget.ui \
    role.ui \
    timetable.ui \
    toolbag.ui \
    toolbag_create.ui \
    toolbag_item.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    animation.qrc \
    res.qrc

DISTFILES += \
    gal_1.png \
    gal_2.png \
    item.txt \
    logo.jpg \
    null.jpg \
    plus_1.png \
    plus_2.png \
    role.png \
    sub_1.png \
    sub_2.png \
    timetable.txt \
    timetable_1.png \
    timetable_2.png \
    tool_1.png \
    tool_2.png

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    menu_bar/InputArea.cpp \
    push_data_db/PushData.cpp \
    reports/ReportQuery.cpp \
    widget.cpp \
    menu_bar/CustomButton.cpp\
    menu_bar/MenuBar.cpp\
    menu_bar/TopBar.cpp

HEADERS += \
    menu_bar/InputArea.h \
    push_data_db/PushData.h \
    reports/ReportQuery.h \
    widget.h\
    menu_bar/CustomButton.h\
    menu_bar/MenuBar.h\
    menu_bar/TopBar.h\
    includes.h

RESOURCES += \
    Resources/icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

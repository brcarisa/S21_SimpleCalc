QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    qcustomplot.cpp \
    ../under_hood/calc_operations.c \
    ../under_hood/credit_calc.c \
    ../under_hood/depo_calc.c \
    ../under_hood/divide_tokens.c \
    ../under_hood/from_infix_to_polish.c \
    ../smart_calc.c \
    ../under_hood/stack_elements.c \
    ../under_hood/valid_input.c \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    qcustomplot.h \
    ../under_hood/credit_calc.h \
    ../under_hood/depo_calc.h \
    ../smart_calc.h \
    ../under_hood/calc_operations.h \
    ../under_hood/divide_tokens.h \
    ../under_hood/from_infix_to_polish.h \
    ../under_hood/stack_elements.h \
    ../under_hood/valid_input.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

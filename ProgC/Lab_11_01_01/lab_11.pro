TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        my_snprintf.c \
    check_unit_tests.c

HEADERS += \
    defines.h \
    my_snprintf.h

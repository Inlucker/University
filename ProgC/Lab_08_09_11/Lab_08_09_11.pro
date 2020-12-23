TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        check_unit_tests.c \
        defines.c \
        io_functions.c \
        main.c \
        mtrx_functions.c

HEADERS += \
    defines.h \
    io_functions.h \
    mtrx_functions.h

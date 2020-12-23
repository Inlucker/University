TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        check_unit_tests.c \
        functions.c \
        io_funcs.c \
        main.c

HEADERS += \
    defines.h \
    functions.h \
    io_funcs.h

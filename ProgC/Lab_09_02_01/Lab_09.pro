TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        functions.c \
        io_funcs.c \
        main.c \
        unit_tests.c

HEADERS += \
    defines.h \
    functions.h \
    io_funcs.h

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    node_funcs.c \
    comporators.c \
    io_funcs.c

HEADERS += \
    defines.h \
    node_funcs.h \
    comporators.h \
    io_funcs.h

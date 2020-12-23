TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        read_args.c \
        sort_funcs.c

HEADERS += \
    defines.h \
    read_args.h \
    sort_funcs.h

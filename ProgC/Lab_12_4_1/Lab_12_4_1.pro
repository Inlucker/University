TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        io_dyn_lib.c \
        io_stat_lib.c \
        key_dyn_lib.c \
        key_stat_lib.c \
        main.c \
        read_args.c \
        sort_funcs.c

HEADERS += \
    defines.h \
    io_dyn_lib.h \
    io_stat_lib.h \
    key_dyn_lib.h \
    key_stat_lib.h \
    read_args.h \
    sort_funcs.h

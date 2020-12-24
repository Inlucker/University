TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        check_unit_tests.c \
        io_dyn_lib.c \
        io_stat_lib.c \
        key_dyn_lib.c \
        key_stat_lib.c \
        main1.c \
        main2.c \
        main3.c \
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

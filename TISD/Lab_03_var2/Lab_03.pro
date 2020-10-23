TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        matrix.cpp \
        sparse.cpp \
        structs.cpp

HEADERS += \
    matrix.h \
    sparse.h \
    structs.h

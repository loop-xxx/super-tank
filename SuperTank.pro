TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    map.c \
    graphics.c \
    tank.c \
    player.c \
    boss.c \
    bullet.c \
    engin.c

HEADERS += \
    graphics.h \
    map.h \
    engin.h \
    link.h \
    player.h \
    boss.h \
    tank.h \
    bullet.h

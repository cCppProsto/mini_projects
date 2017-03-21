TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c11

INCLUDEPATH += ../external_libs/glfw/include/
INCLUDEPATH += ../external_libs/glut/include/

INCLUDEPATH += ../../../tools_src/

SOURCES += main.c \
    gl_menu.c \
    ../../../tools_src/menu.c

HEADERS += \
    gl_menu.h \
    ../external_libs/glfw/include/glfw3.h \
    ../external_libs/glfw/include/glfw3native.h \
    ../external_libs/glut/include/glut.h \
    ../../../tools_src/menu.h \
    common.h

QT   += opengl
LIBS += -lopengl32

win32: LIBS += -L$$PWD/../external_libs/glfw/lib/ -lglfw3
win32: LIBS += -L$$PWD/../external_libs/glut/lib/ -lglut32
win32: LIBS += -lgdi32

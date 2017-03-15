TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c11

INCLUDEPATH += ../external_libs/glfw/include/
INCLUDEPATH += ../external_libs/glut/include/
INCLUDEPATH += ../common/

SOURCES += main.c \
    drawer.c \
    glfw_engine.c \
    paratrooper.c \
    resources.c \
    ../common/fps_tool.c
    ../common/fps_tool.c

HEADERS += \
    common.h \
    drawer.h \
    glfw_engine.h \
    paratrooper.h \
    ../external_libs/glfw/include/glfw3.h \
    ../external_libs/glfw/include/glfw3native.h \
    ../external_libs/glut/include/glut.h \
    ../common/fps_tool.h

QT   += opengl
LIBS += -lopengl32

win32: LIBS += -L$$PWD/../external_libs/glfw/lib/ -lglfw3
win32: LIBS += -L$$PWD/../external_libs/glut/lib/ -lglut32
win32: LIBS += -lgdi32

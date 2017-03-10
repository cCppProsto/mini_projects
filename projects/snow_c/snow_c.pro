TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c11

QT   += opengl
LIBS += -lopengl32

SOURCES += main.c \
    glfw_engine.c \
    fps_tool.c

win32: LIBS += -L$$PWD/glfw/lib/ -lglfw3 -lgdi32

HEADERS += \
    glfw/include/glfw3.h \
    glfw/include/glfw3native.h \
    glfw_engine.h \
    fps_tool.h

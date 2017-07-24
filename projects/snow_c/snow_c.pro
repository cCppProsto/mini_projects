TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c11

SOURCES += main.c \
    glfw_engine.c \
    fps_tool.c

HEADERS += \
    glfw/include/glfw3.h \
    glfw/include/glfw3native.h \
    glfw_engine.h \
    fps_tool.h

QT   += opengl

LIBS += -lGL -lGLU -lglut
LIBS += -lglfw
LIBS += -lX11 -lXrandr -lXinerama -lXxf86vm -lXcursor -lpthread -ldl

win32: LIBS += -L$$PWD/../../../external_libs/glfw/lib/ -lglfw3
win32: LIBS += -lgdi32 -L$$PWD/../../../external_libs/glut/lib/ -lglut32
win32: LIBS += -lopengl32

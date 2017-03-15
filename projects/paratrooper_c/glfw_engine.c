#include <stdio.h>
#include "glfw3.h"
#include <GL/gl.h>

#include <time.h>
#include "common.h"
#include "fps_tool.h"
#include "paratrooper.h"

//------------------------------------------------------------------------------
GLFWwindow* window;

int    g_scr_width     = 0;
int    g_scr_height    = 0;
float  g_w_ratio       = 0.f;
float  g_h_ratio       = 0.f;
double g_cursor_x      = 0.;
double g_cursor_y      = 0.;
//------------------------------------------------------------------------------
void resize_clb     (GLFWwindow*, int, int);
void mouse_click_clb(GLFWwindow*, int, int, int);
void key_click_clb  (GLFWwindow*, int, int, int, int);
//------------------------------------------------------------------------------
int gl_init()
{
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              "snow",
                              IS_FULL_SCREEN ? glfwGetPrimaryMonitor() : NULL,
                              NULL);

    glfwSetWindowPos(window,0,20);

    glfwGetWindowSize(window, &g_scr_width, &g_scr_height);
    g_w_ratio = (float)g_scr_width  / (float)SCREEN_WIDTH;
    g_h_ratio = (float)g_scr_height / (float)SCREEN_HEIGHT;

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback        (window, key_click_clb);
    glfwSetWindowSizeCallback (window, resize_clb);
    glfwSetMouseButtonCallback(window, mouse_click_clb);

    glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
    glfwSwapInterval(1);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    glPointSize(1);

    return 1;
}
//------------------------------------------------------------------------------
void engine_main()
{
    if(gl_init() == -1)
        return;

    paratrooper_init();

    fps_set_fps(30);
    while (!glfwWindowShouldClose(window))
    {
        fps_start();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        paratrooper_processing();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();

        fps_wait();
    }
    glfwTerminate();
}
//------------------------------------------------------------------------------
void resize_clb(GLFWwindow *apWindow, int aWidth, int aHeight)
{
    glViewport(0, 0, aWidth, aHeight);

    glfwGetWindowSize(apWindow, &g_scr_width, &g_scr_height);
    g_w_ratio = (float)g_scr_width  / (float)SCREEN_WIDTH;
    g_h_ratio = (float)g_scr_height / (float)SCREEN_HEIGHT;
}
//------------------------------------------------------------------------------
void mouse_click_clb(GLFWwindow *apWindow, int aBtn, int aAction, int aMods)
{
    if(aBtn == GLFW_MOUSE_BUTTON_1)
    {
        switch(aAction)
        {
            case GLFW_PRESS:
            {
                glfwGetCursorPos(apWindow, &g_cursor_x, &g_cursor_y);
                //int ix = ((float)cursor_x / w_ratio);
                //int iy = ((float)cursor_y / h_ratio);
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------
void key_click_clb(GLFWwindow *apWindow, int aKey, int aScanCode, int aAction, int aMods)
{
    if(aAction == GLFW_PRESS || aAction == GLFW_REPEAT)
    {
        switch(aKey)
        {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(apWindow, GL_TRUE);
                break;
            }
            case GLFW_KEY_RIGHT:
            {
                gun_rotate(RIGHT);
                break;
            }
            case GLFW_KEY_LEFT:
            {
                gun_rotate(LEFT);
                break;
            }
            case GLFW_KEY_SPACE:
            {
                shot();
                break;
            }
        }
    }
}

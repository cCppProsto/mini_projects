#include <stdio.h>

#include "glfw/include/glfw3.h"
#include <GL/gl.h>

#include "fps_tool.h"

//------------------------------------------------------------------------------
#define SCREEN_WIDTH        800
#define SCREEN_HEIGHT       600
#define IS_FULL_SCREEN      0
//------------------------------------------------------------------------------
GLFWwindow* window;

GLuint scra[SCREEN_HEIGHT + 1][SCREEN_WIDTH] = {{0}};
int dx        = 0;
int dy        = 0;
int pointSize = 0;

int    scr_width     = 0;
int    scr_height    = 0;
float  w_ratio       = 0.f;
float  h_ratio       = 0.f;
double cursor_x      = 0.;
double cursor_y      = 0.;
int    snows_on_line = 10;
//------------------------------------------------------------------------------
void snow_draw();
void snow_draw_v2();
void crear_square(int,int);
//------------------------------------------------------------------------------
void resize_clb     (GLFWwindow*, int, int);
void key_click_clb  (GLFWwindow*, int, int, int, int);
void mouse_click_clb(GLFWwindow*, int, int, int);
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

    glfwGetWindowSize(window, &scr_width, &scr_height);

    w_ratio = (float)scr_width  / (float)SCREEN_WIDTH;
    h_ratio = (float)scr_height / (float)SCREEN_HEIGHT;

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

    return 1;
}
//------------------------------------------------------------------------------
void engine_main()
{
    if(gl_init() == -1)
        return;

    fps_set_fps(60);
    while (!glfwWindowShouldClose(window))
    {
        fps_start();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //snow_draw();
        snow_draw_v2();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();

        fps_wait();
    }
    glfwTerminate();
}
//------------------------------------------------------------------------------
void resize_clb(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    glfwGetWindowSize(window, &scr_width, &scr_height);
    w_ratio = (float)scr_width  / (float)SCREEN_WIDTH;
    h_ratio = (float)scr_height / (float)SCREEN_HEIGHT;
}
//------------------------------------------------------------------------------
void key_click_clb(GLFWwindow *pWindow, int aKey, int aScanCode, int aAction, int aMods)
{
    if(aKey == GLFW_KEY_ESCAPE && aAction == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
}
//------------------------------------------------------------------------------
void mouse_click_clb(GLFWwindow *pWindow, int aBtn, int aAction, int aMods)
{
    if(aBtn == GLFW_MOUSE_BUTTON_1)
    {
        switch(aAction)
        {
            case GLFW_PRESS:
            {
                glfwGetCursorPos(pWindow, &cursor_x, &cursor_y);

                int ix = ((float)cursor_x / w_ratio);
                int iy = ((float)cursor_y / h_ratio);
                crear_square(ix, iy);
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------
void snow_draw()
{
    glColor3ub(254, 254, 254);

    int tmp = SCREEN_WIDTH / snows_on_line;
    for(int i = 0; i < SCREEN_WIDTH; i += tmp)
        scra[1][i+ rand() % tmp] = 1;

    for(int i = SCREEN_HEIGHT - 2; i > 0; --i)
    {
       for(int j = 0; j < SCREEN_WIDTH; ++j)
       {
           if(scra[i][j] == 1)
           {
                dx        = (rand() % 2) ? 1 : -1;
                dy        =  1;
                pointSize = (rand() % 2) + 1;

                if(scra[i + dy][j + dx] == 0)
                {
                    scra[i][j] = 0;
                    scra[i + dy][j + dx] = 1;

                    glPointSize(pointSize);
                    glBegin(GL_POINTS);
                        glVertex2i(j+dx, i+dy);
                    glEnd();
                }
                else
                {
                    glPointSize(3);
                    glBegin(GL_POINTS);
                        glVertex2i(j, i);
                    glEnd();
                }
           }
       }
    }

    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2i(0,            SCREEN_HEIGHT - 1);
        glVertex2i(SCREEN_WIDTH, SCREEN_HEIGHT - 1);
    glEnd();
}
//------------------------------------------------------------------------------
void snow_draw_v2()
{
    glColor3ub(254, 254, 254);

    int tmp = SCREEN_WIDTH / snows_on_line;
    for(int i = 0; i < SCREEN_WIDTH; i += tmp)
        scra[1][i+ rand() % tmp] = 1;

    glPointSize(2);
    glBegin(GL_POINTS);
    for(int i = SCREEN_HEIGHT - 4; i > 0; --i)
    {
       for(int j = 0; j < SCREEN_WIDTH; ++j)
       {
           if(scra[i][j] == 1)
           {
                dx        = (rand() % 2) ? 1 : -1;
                dy        =  1;
                if(scra[i + dy][j + dx] == 0)
                {
                    scra[i][j] = 0;
                    scra[i + dy][j + dx] = 1;
                    glVertex2i(j+dx, i+dy);
                }
                else
                    glVertex2i(j, i);
           }
       }
    }
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2i(0,            SCREEN_HEIGHT - 1);
        glVertex2i(SCREEN_WIDTH, SCREEN_HEIGHT - 1);
    glEnd();
}
//------------------------------------------------------------------------------
void crear_square(int aX, int aY)
{
    scra[aY][aX] = 0;

    for(int i = -10; i < 11; ++i)
    {
        if((aX + i) >= 0 && (aX + i) < SCREEN_WIDTH)
        {
            for(int j = -10; j < 11; ++j)
            {
                if((aY + j) >= 0 &&
                   (aY + j) < SCREEN_HEIGHT)
                    scra[aY + j][aX + i] = 0;
            }
        }
    }
}

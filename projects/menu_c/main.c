#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "glfw3.h"
#include <GL/gl.h>

#include <conio.h>

#include "common.h"
#include "menu.h"
#include "gl_menu.h"

#define IS_FULL_SCREEN  0
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

//------------------------------------------------------------------------------
GLFWwindow* window;

bool   gAsciiRedraw = true;
sMenu *gMenu        = 0;
int    gKey         = 0;
//------------------------------------------------------------------------------

void menu_processing();

void ascii_draw(sMenu *apMenu);

int  gl_init();
void resize_clb(GLFWwindow *, int, int);
void key_click_clb(GLFWwindow*, int, int, int, int);

void opengl_draw();

sMenu *init_menu();
void start_menu_init(sMenu *, sMenuItem *);
void hard_menu_init(sMenu *, sMenuItem *);
void options_menu_init(sMenu *, sMenuItem *);

//------------------------------------------------------------------------------
int main()
{
    if(gl_init() == -1)
        return 1;

    gMenu = init_menu();

    ascii_draw(gMenu);
    while (!glfwWindowShouldClose(window))
    {
        if(gAsciiRedraw)
            ascii_draw(gMenu);
        opengl_draw();
    }

    glfwTerminate();

    menu_destroy(&gMenu);
    return 0;
}
//------------------------------------------------------------------------------
sMenu * init_menu()
{
    sMenu     *menu = menu_create();
    sMenu     *subMenu = 0;
    sMenuItem *item = 0;

    item = menu_add_item(menu, "Start", MENU_START);
    start_menu_init(menu, item);

    item = menu_add_item(menu, "Options", MENU_OPTIONS);
    options_menu_init(menu, item);

    menu_add_item(menu, "About", MENU_ABOUT);
    menu_add_item(menu, "Exit", MENU_EXIT);

    return menu;
}
//------------------------------------------------------------------------------
void start_menu_init(sMenu *apMenu, sMenuItem *apItem)
{
    sMenu *subMenu = 0;
    sMenuItem *item = 0;

    subMenu = menu_create_sub_menu(apMenu, apItem);
    menu_add_item(subMenu,      "easy",     MENU_EASY);
    menu_add_item(subMenu,      "medium",   MENU_MEDIUM);

    item = menu_add_item(subMenu, "hard",   MENU_HARD);
    hard_menu_init(subMenu, item);
}
//--------------------------------------------------------------------
void hard_menu_init(sMenu *apMenu, sMenuItem *apItem)
{
    sMenu     *subMenu = 0;

    subMenu = menu_create_sub_menu(apMenu, apItem);
    menu_add_item(subMenu, "man", MENU_MAN);
    menu_add_item(subMenu, "woman", MENU_WOMAN);
}
//--------------------------------------------------------------------
void options_menu_init(sMenu *apMenu, sMenuItem *apItem)
{
    sMenu *subMenu = 0;
    subMenu = menu_create_sub_menu(apMenu, apItem);
    menu_add_item(subMenu, "audio", MENU_AUDIO);
    menu_add_item(subMenu, "video", MENU_VIDEO);
    menu_add_item(subMenu, "other", MENU_OTHER);
}
//--------------------------------------------------------------------
void ascii_draw(sMenu *apMenu)
{
    system("cls");
    sMenuItem *it = menu_first_item(apMenu);
    do
    {
        if (menu_item_is_selected(apMenu, it))
            printf("[%s]\n", it->value.str);
        else
            printf("%s\n", it->value.str);
        it = menu_next_item(it);
    } while (it != 0);
    gAsciiRedraw = false;
}
//------------------------------------------------------------------------------
int gl_init()
{
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              "menu",
                              IS_FULL_SCREEN ? glfwGetPrimaryMonitor() : NULL,
                              NULL);

    glfwSetWindowPos(window,0,20);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback        (window, key_click_clb);
    glfwSetWindowSizeCallback (window, resize_clb);
    //glfwSetMouseButtonCallback(window, mouse_click_clb);

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
    glLineWidth(1);

    return 1;
}
//------------------------------------------------------------------------------
void resize_clb(GLFWwindow *apWindow, int aWidth, int aHeight)
{
    glViewport(0, 0, aWidth, aHeight);
}
//------------------------------------------------------------------------------
void key_click_clb(GLFWwindow *apWindow, int aKey, int aScanCode, int aAction, int aMods)
{
    if(aAction == GLFW_PRESS || aAction == GLFW_REPEAT)
    {
        switch(aKey)
        {
            case GLFW_KEY_ENTER:
            {
                sMenu *tmp = menu_sub_enter(gMenu);
                if (tmp != gMenu)
                    gMenu = tmp;
                else
                {
                    if (menu_current_value(gMenu)->id == MENU_EXIT)
                        glfwSetWindowShouldClose(apWindow, GL_TRUE);
                }
                gAsciiRedraw = true;
                break;
            }
            case GLFW_KEY_ESCAPE:
            {
                gMenu = menu_sub_leave(gMenu);
                gAsciiRedraw = true;
                break;
            }
            case GLFW_KEY_UP:
            {
                if (!menu_select_prev(gMenu))
                    menu_select_last(gMenu);

                gAsciiRedraw = true;
                break;
            }
            case GLFW_KEY_DOWN:
            {
                if (!menu_select_next(gMenu))
                    menu_select_first(gMenu);

                gAsciiRedraw = true;
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------
void opengl_draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gl_menu_draw(gMenu);

    glfwSwapBuffers(window);
    glfwPollEvents();
}


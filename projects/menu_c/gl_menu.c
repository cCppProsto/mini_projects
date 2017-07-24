#include <GL/gl.h>
//#include <GL/glaux.h>
#include <GL/glu.h>
#include <glfw3.h>
#include <string.h>

#include "glut.h"
#include "gl_menu.h"

void gl_draw_item(int, int, sMenuItem *);
void gl_draw_selected_item(int, int, sMenuItem *);

void gl_draw_str(int, int, char*);

typedef struct
{
    int x;
    int y;
}sPos;

sPos animated_pos[] =
{
    {0,   0}
   ,{0,   1}
   ,{0,   2}
   ,{0,   3}
   ,{1,   0}
   ,{1,   1}
   ,{1,   2}
   ,{1,   3}
   ,{2,   0}
   ,{2,   1}
   ,{2,   2}
   ,{2,   3}
   ,{3,   0}
   ,{3,   1}
   ,{3,   2}
   ,{3,   3}
   ,{0,  -1}
   ,{0,  -2}
   ,{0,  -3}
   ,{-1,  0}
   ,{-1, -1}
   ,{-1, -2}
   ,{-1, -3}
   ,{-2,  0}
   ,{-2, -1}
   ,{-2, -2}
   ,{-2, -3}
   ,{-3,  0}
   ,{-3, -1}
   ,{-3, -2}
   ,{-3, -3}
};

//------------------------------------------------------------------------------
void gl_menu_draw(sMenu *apMenu)
{
    static sMenuItem *i = 0;
    static int        x = 0;
    static int        y = 0;

    x = 350;
    y = 180;

    i = menu_first_item(apMenu);
    do
    {
        if(menu_item_is_selected(apMenu, i))
            gl_draw_selected_item(x, y, i);
        else
            gl_draw_item(x, y, i);

        y += 50;
        i = menu_next_item(i);
    }while(i);
}
//------------------------------------------------------------------------------
void gl_draw_item(int aX, int aY, sMenuItem *apItem)
{
    glColor3ub(0, 254,0);
    gl_draw_str(aX, aY, apItem->value.str);
}
//------------------------------------------------------------------------------
void gl_draw_selected_item(int aX, int aY, sMenuItem *apItem)
{
    static double start = 0.;
    static int    i     = 0;

    if((glfwGetTime() - start) > 0.2)
    {
        start = glfwGetTime();
        i = rand() % 31;
    }

    glColor3ub(254, 0, 0);
    gl_draw_str(aX + animated_pos[i].x,
                aY + animated_pos[i].y,
                apItem->value.str);
}
//------------------------------------------------------------------------------
void gl_draw_str(int aX, int aY, char *apStr)
{
    static int i = 0;
    i = 0;
    do
    {
        glRasterPos2i( aX + (i*15), aY);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, apStr[i]);
    }while(apStr[++i]);
}


/*
void ellipse(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0
    float y = 0;

    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x * rx + cx, y * ry + cy);

        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}
*/

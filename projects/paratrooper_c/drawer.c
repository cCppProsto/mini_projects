#include <GL/gl.h>
#include "glfw3.h"

#include "resources.c"
#include "drawer.h"

/*
    0 - 0,     0,   0       black - unused
    1 - 84,  254, 254       ligth blue
    2 - 254, 254, 254       white
    3 - 254,  84, 254       purple
*/

sColor point_color[4] =
{
    {0,     0,   0}
   ,{84,  254, 254}
   ,{254, 254, 254}
   ,{254,  84, 254}
};

void trooper_draw(int const *, int const *);
void trooper_brolly_draw(int const *, int const *);
void helicopter_draw_left(int const *, int const *);
void helicopter_draw_rigth(int const *, int const *);

void unit_draw(sUnits const *aUnit)
{
    switch(aUnit->type)
    {
        case TROOPER:
        {
            trooper_draw(&aUnit->pos.x, &aUnit->pos.y);
            break;
        }
        case TROOPER_BROLLY:
        {
            trooper_brolly_draw(&aUnit->pos.x, &aUnit->pos.y);
            break;
        }
    }
}
//------------------------------------------------------------------------------
void helicopter_draw(sHelicopter const *apHelicopter)
{
    switch(apHelicopter->direction)
    {
        case HELICOPTER_LEFT:
        {
            helicopter_draw_left(&apHelicopter->pos.x, &apHelicopter->pos.y);
            break;
        }
        case HELICOPTER_RIGHT:
        {
            helicopter_draw_rigth(&apHelicopter->pos.x, &apHelicopter->pos.y);
            break;
        }
    }
}
//------------------------------------------------------------------------------
void turret_draw(sGunTurret const *apTurret)
{
    sColor const *colBase  = &apTurret->base.color;
    sColor const *colTower = &apTurret->tower.color;
    sColor const *colGun   = &apTurret->gun.color;

    //      DRAW BASE
    glColor3ub(colBase->r, colBase->g, colBase->b);
    glRecti(apTurret->base.ltpos.x, apTurret->base.ltpos.y,
            apTurret->base.rbpos.x, apTurret->base.rbpos.y);

    //      DRAW GUN
    glColor3ub(colGun->r, colGun->g, colGun->b);
    glLineWidth(4);
    glBegin(GL_LINES);
        glVertex2i(apTurret->gun.pos_s.x, apTurret->gun.pos_s.y);
        glVertex2i(apTurret->gun.pos_e.x, apTurret->gun.pos_e.y);
    glEnd();

    //      DRAW TOWER
    glColor3ub(colTower->r, colTower->g, colTower->b);
    glRecti(apTurret->tower.ltpos.x, apTurret->tower.ltpos.y,
            apTurret->tower.rbpos.x, apTurret->tower.rbpos.y);
}
//------------------------------------------------------------------------------
void trooper_draw(int const *apX, int const *apY)
{
    static unsigned frame        = 0;
    static double   start        = 0.;
    static unsigned p            = 0;
    static unsigned prev_p_color = 1;
    static unsigned index        = 0;

    if((glfwGetTime() - start) > 0.333)
    {
        ++frame;
        if(frame >= trooper_frames)
            frame = 0;
        start = glfwGetTime();
    }

    glBegin(GL_POINTS);
    for(int i = 0; i < 16; ++i)
        for(int j = 0; j < 8; ++j)
        {
            p = trooper[frame][i][j];
            if(p > 0)
            {
                if(prev_p_color != p)
                {
                    index = p;
                    glColor3ub(point_color[index].r, point_color[index].g, point_color[index].b);
                    prev_p_color = p;
                }
                glVertex2i(*apX + j, *apY + i);
            }
        }
    glEnd();
}
//------------------------------------------------------------------------------
void trooper_brolly_draw(int const *apX, int const *apY)
{
    static unsigned p            = 0;
    static unsigned frame        = 0;
    static double   start        = 0.;
    static unsigned prev_p_color = 1;
    static unsigned index        = 0;

    if((glfwGetTime() - start) > 0.333)
    {
        ++frame;
        if(frame >= trooper_brolly_frames)
            frame = 0;
        start = glfwGetTime();
    }

    glBegin(GL_POINTS);
    for(int i = 0; i < 44; ++i)
        for(int j = 0; j < 24; ++j)
        {
            p = trooper_brolly[frame][i][j];
            if(p > 0)
            {
                if(prev_p_color != p)
                {
                    index = p;
                    glColor3ub(point_color[index].r, point_color[index].g, point_color[index].b);
                    prev_p_color = p;
                }
                glVertex2i(*apX + j, *apY + i);
            }
        }
    glEnd();
}

//------------------------------------------------------------------------------
void helicopter_draw_left(int const *apX, int const *apY)
{
    static unsigned p            = 0;
    static unsigned frame        = 0;
    static double   start        = 0.;
    static unsigned prev_p_color = 1;
    static unsigned index        = 0;

    if((glfwGetTime() - start) > 0.333)
    {
        ++frame;
        if(frame >= helicopter_left_frames)
            frame = 0;
        start = glfwGetTime();
    }

    glBegin(GL_POINTS);
    for(int i = 0; i < 20; ++i)
        for(int j = 0; j < 46; ++j)
        {
            p = helicopter_left[frame][i][j];
            if(p > 0)
            {
                if(prev_p_color != p)
                {
                    index = p;
                    glColor3ub(point_color[index].r, point_color[index].g, point_color[index].b);
                    prev_p_color = p;
                }
                glVertex2i(*apX + j, *apY + i);
            }
        }
    glEnd();
}
//------------------------------------------------------------------------------
void helicopter_draw_rigth(int const *apX, int const *apY)
{
    static unsigned p            = 0;
    static unsigned frame        = 0;
    static double   start        = 0.;
    static unsigned prev_p_color = 1;
    static unsigned index        = 0;

    if((glfwGetTime() - start) > 0.333)
    {
        ++frame;
        if(frame >= helicopter_left_frames)
            frame = 0;
        start = glfwGetTime();
    }

    glBegin(GL_POINTS);
    for(int i = 0; i < 20; ++i)
        for(int j = 0; j < 46; ++j)
        {
            p = helicopter_left[frame][i][j];
            if(p > 0)
            {
                if(prev_p_color != p)
                {
                    index = p;
                    glColor3ub(point_color[index].r, point_color[index].g, point_color[index].b);
                    prev_p_color = p;
                }
                glVertex2i(*apX + (45-j), *apY + i);
            }
        }
    glEnd();
}
//------------------------------------------------------------------------------
unsigned is_unit_cross(sfPos const *apPoint, sUnits const *apUnit)
{
    static int x = 0;
    static int y = 0;

    if(apUnit->type == TROOPER_BROLLY)
    {
        x = apPoint->x;
        y = apPoint->y;

        if(
            (y >= apUnit->pos.y) &&
            (y <= apUnit->pos.y + TROOPER_BROLLY_H)
            )
        {
            if( (x >= apUnit->pos.x) &&
                (x <= apUnit->pos.x + TROOPER_BROLLY_W)
               )
            {
                return 1;
            }
        }
    }
    return 0;
}

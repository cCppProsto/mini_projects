#include <GL/gl.h>
#include <GL/glaux.h>
#include <GL/glu.h>
#include <glfw3.h>
#include <math.h>
#include <stdlib.h>

#include "common.h"
#include "paratrooper.h"
#include "drawer.h"

#include "glut.h"

//------------------------------------------------------------------------------
float rad_sin[361] = {0.f};
float rad_cos[361] = {0.f};

void  pre_calculate();
float rcos(int);
float rsin(int);

//------------------------------------------------------------------------------
sGunTurret  gTurret;
sHelicopter gHelicopter1;
sHelicopter gHelicopter2;

unsigned g_shots_count = 0;

sShot ga_shots[SHOTS_COUNT] = {[0 ... (SHOTS_COUNT-1)] = {
                                p1:      {0.f, 0.f},
                                p2:      {0.f, 0.f},
                                .angle   = 0,
                                .dx      = 0.f,
                                .dy      = 0.f,
                                .lenght  = SHOT_INIT_LENGHT,
                                .speed   = SHOT_SPEED,
                                .is_live = 0}};

/*
|  0  | 40  |  80 | 120 | 160 | 200 | 240 |
| 39  | 79  | 119 | 159 | 199 | 239 | 279 |
|     |     |     |     |     |     |     |
|  +  |  +  |  +  |  +  |  +  |  +  |  +  |
| [0] | [1] | [2] | [3] | [4] | [5| | [6] |

| 280 | 320 |
| 319 | 359 |
|     |     |
|  -  |  -  |
| [7] | [8] |

| 360 | 400 | 440 | 480 | 520 | 560 | 600 |
| 399 | 439 | 479 | 519 | 559 | 599 | 439 |
|     |     |     |     |     |     |     |
|  +  |  +  |  +  |  +  |  +  |  +  |  +  |
| [9] | [10]| [11]| [12]| [13]| [14]| [15]|
*/
sUnits paratrooper_brolly_array[COLUMNS_COUNT][PAR_COUNT_ON_COLUMN]   =
{
    [0 ... 15] = { [0 ... 3] = {{.x = 0,.y = -1}, .type = TROOPER_BROLLY}}
};

int parr_brolly_count[COLUMNS_COUNT] = {0,0,0,0,0,0,0,
                                        PAR_COUNT_ON_COLUMN, PAR_COUNT_ON_COLUMN,
                                        0,0,0,0,0,0,0};

int column_pos[COLUMNS_COUNT]  = {0,40,80,120,160,200,240,280,320,360,400,440,480,520,560,600};

//------------------------------------------------------------------------------
void turret_init();
void helicopters_init();

void processing();
void draw();

void recalc_gun_cource();

void helicopters_doing();
void helicopter_move(sHelicopter *);
void helicopter_trooper_generate(sHelicopter const *);

void paratrooper_doing();
void paratroopers_brolly_move();
void paratrooper_brolly_draw();

void shot_doing();
void shot_draw();
//------------------------------------------------------------------------------
void paratrooper_init()
{
    pre_calculate();
    turret_init();
    helicopters_init();
}
//------------------------------------------------------------------------------
void turret_init()
{
    // GUN ----->     /
    //              _/
    //             |.|  <------- TOWER
    //           +-----+
    //           |     | <------ BASE
    //           +-----+

    //>>>>>> BASE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    gTurret.base.ltpos.x = TURRET_BASE_INIT_X;
    gTurret.base.ltpos.y = TURRET_BASE_INIT_Y;
    gTurret.base.rbpos.x = gTurret.base.ltpos.x + TURRET_BASE_WIDTH;
    gTurret.base.rbpos.y = gTurret.base.ltpos.y + TURRET_BASE_HEIGHT;
    gTurret.base.color.r = 160;
    gTurret.base.color.g = 160;
    gTurret.base.color.b = 160;
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //>>>>>> TOWER >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    gTurret.tower.ltpos.x = (gTurret.base.ltpos.x + TURRET_BASE_WIDTH /4 );
    gTurret.tower.ltpos.y = gTurret.base.ltpos.y - (TURRET_BASE_HEIGHT / 2);
    gTurret.tower.rbpos.x = gTurret.tower.ltpos.x + TURRET_BASE_WIDTH/2;
    gTurret.tower.rbpos.y = gTurret.base.ltpos.y;
    gTurret.tower.color.r = 0;
    gTurret.tower.color.g = 160;
    gTurret.tower.color.b = 60;
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //>>>>>> GUN >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    gTurret.gun.pos_s.x = gTurret.tower.ltpos.x + TURRET_BASE_WIDTH / 4;
    gTurret.gun.pos_s.y = gTurret.tower.ltpos.y + 5;

    //
    //    270
    //180      0
    //    90
    gTurret.gun.angle   = 270;

    recalc_gun_cource();

    gTurret.gun.color.r = 0;
    gTurret.gun.color.g = 20;
    gTurret.gun.color.b = 200;
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}
//------------------------------------------------------------------------------
void helicopters_init()
{
    gHelicopter1.direction  = HELICOPTER_LEFT;
    gHelicopter1.pos.x      = HELICOPTER_INIT_X_R;
    gHelicopter1.pos.y      = HELICOPTER_INIT_Y_R;
    gHelicopter1.isGenerate = 1;

    gHelicopter2.direction  = HELICOPTER_RIGHT;
    gHelicopter2.pos.x      = HELICOPTER_INIT_X_L;
    gHelicopter2.pos.y      = HELICOPTER_INIT_Y_L;
    gHelicopter2.isGenerate = 1;
}
//------------------------------------------------------------------------------
void processing()
{
    helicopters_doing();
    paratrooper_doing();
    shot_doing();
}
//------------------------------------------------------------------------------
void draw()
{
    turret_draw(&gTurret);

    helicopter_draw(&gHelicopter1);
    helicopter_draw(&gHelicopter2);

    paratrooper_brolly_draw();

    shot_draw();

    //glColor3ub(0, 254,0);
    //glRasterPos2i( 100, 100);
    //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
}
//------------------------------------------------------------------------------
void paratrooper_processing()
{
    processing();

    draw();
}//------------------------------------------------------------------------------
void helicopters_doing()
{
    static double start = 0.;

    helicopter_move(&gHelicopter1);
    helicopter_move(&gHelicopter2);

    if(gHelicopter1.isGenerate)
    {
        helicopter_trooper_generate(&gHelicopter1);
        gHelicopter1.isGenerate = 0;
    }

    if(gHelicopter2.isGenerate)
    {
        helicopter_trooper_generate(&gHelicopter2);
        gHelicopter2.isGenerate = 0;
    }

    if((glfwGetTime() - start) > 0.6)
    {
        start = glfwGetTime();
        gHelicopter1.isGenerate = 1;
        gHelicopter2.isGenerate = 1;
    }
}
//------------------------------------------------------------------------------
void helicopter_move(sHelicopter *apHelicopter)
{
    switch(apHelicopter->direction)
    {
        case HELICOPTER_LEFT:
        {
            apHelicopter->pos.x -= HELICOPTER_DX;
            if(apHelicopter->pos.x < 0)
            {
                apHelicopter->pos.x     = HELICOPTER_INIT_X_L;
                apHelicopter->direction = HELICOPTER_RIGHT;
            }
            break;
        }
        case HELICOPTER_RIGHT:
        {
            apHelicopter->pos.x += HELICOPTER_DX;
            if(apHelicopter->pos.x > HELICOPTER_INIT_X_R)
            {
                apHelicopter->pos.x     = HELICOPTER_INIT_X_R;
                apHelicopter->direction = HELICOPTER_LEFT;
            }
            break;
        }
    }
}
//------------------------------------------------------------------------------
void helicopter_trooper_generate(sHelicopter const *apHelicopter)
{
    static int *px = 0;
    static int *py = 0;
    static int i   = 0;

    px = &apHelicopter->pos.x;
    py = &apHelicopter->pos.y;

    // |                                              |  - helicopter width 46
    // |                        |                        - brolly width     24
    // |                                        |        - column width     40
    i = *px / 40;
    if(*px < (column_pos[i] + 16))
    {
        if((rand() % 5) & 0x01)
        {
            if(parr_brolly_count[i] < PAR_COUNT_ON_COLUMN)
            {
                int index = 0;
                while(paratrooper_brolly_array[i][index++].pos.y > 0)
                    ;

                paratrooper_brolly_array[i][index-1].pos.x = *px + 8;
                paratrooper_brolly_array[i][index-1].pos.y = *py;

                ++parr_brolly_count[i];
            }
        }
    }
}
//------------------------------------------------------------------------------
void paratrooper_doing()
{
    paratroopers_brolly_move();
}
//------------------------------------------------------------------------------
void paratroopers_brolly_move()
{
    static unsigned i     = 0;
    static sUnits *gpUnit = 0;
    i = 0;

    while(i < COLUMNS_COUNT)
    {
        gpUnit = &paratrooper_brolly_array[i][0];
        if(gpUnit->pos.y >= 0)
        {
            if((gpUnit->pos.y + TROOPER_BROLLY_H) < SCREEN_HEIGHT)
                ++gpUnit->pos.y;
            else
            {
                gpUnit->pos.y = -1;
                --parr_brolly_count[i];
            }
        }

        gpUnit = &paratrooper_brolly_array[i][1];
        if(gpUnit->pos.y >= 0)
        {
            if((gpUnit->pos.y + TROOPER_BROLLY_H) < SCREEN_HEIGHT)
                ++gpUnit->pos.y;
            else
            {
                gpUnit->pos.y = -1;
                --parr_brolly_count[i];
            }
        }

        gpUnit = &paratrooper_brolly_array[i][2];
        if(gpUnit->pos.y >= 0)
        {
            if((gpUnit->pos.y + TROOPER_BROLLY_H) < SCREEN_HEIGHT)
                ++gpUnit->pos.y;
            else
            {
                gpUnit->pos.y = -1;
                --parr_brolly_count[i];
            }
        }

        gpUnit = &paratrooper_brolly_array[i][3];
        if(gpUnit->pos.y >= 0)
        {
            if((gpUnit->pos.y + TROOPER_BROLLY_H) < SCREEN_HEIGHT)
                ++gpUnit->pos.y;
            else
            {
                gpUnit->pos.y = -1;
                --parr_brolly_count[i];
            }
        }
        ++i;
    }
}
//------------------------------------------------------------------------------
void paratrooper_brolly_draw()
{
    static unsigned     i = 0;
    static sUnits *gpUnit = 0;

    i = 0;
    while(i < COLUMNS_COUNT)
    {
        gpUnit = &paratrooper_brolly_array[i][0];
        if(gpUnit->pos.y >= 0)
            unit_draw(gpUnit);

        gpUnit = &paratrooper_brolly_array[i][1];
        if(gpUnit->pos.y >= 0)
            unit_draw(gpUnit);

        gpUnit = &paratrooper_brolly_array[i][2];
        if(gpUnit->pos.y >= 0)
            unit_draw(gpUnit);

        gpUnit = &paratrooper_brolly_array[i][3];
        if(gpUnit->pos.y >= 0)
            unit_draw(gpUnit);

        ++i;
    }
}
//------------------------------------------------------------------------------
void recalc_gun_cource()
{
    // rad  = grad*Pi / 180;
    // grad = rad*180 / Pi;
    gTurret.gun.pos_e.x = gTurret.gun.pos_s.x + (GUN_LENGHT * rcos(gTurret.gun.angle));
    gTurret.gun.pos_e.y = gTurret.gun.pos_s.y + (GUN_LENGHT * rsin(gTurret.gun.angle));
}
//------------------------------------------------------------------------------
void gun_rotate(eGunRotate aValue)
{
    switch(aValue)
    {
        case LEFT:
        {
            gTurret.gun.angle -= 4;

            if(gTurret.gun.angle <= 180)
                gTurret.gun.angle = 180;
            break;
        }
        case RIGHT:
        {
            gTurret.gun.angle += 4;
            if(gTurret.gun.angle >= 360)
                gTurret.gun.angle = 360;
            break;
        }
    }
    recalc_gun_cource();
}
//------------------------------------------------------------------------------
void shot()
{
    static unsigned i = 0;
    static sShot *psh = 0;
    i = 0;
    while(i < SHOTS_COUNT )
    {
        if(ga_shots[i].is_live == 0)
            break;
        ++i;
    }

    if(i >= SHOTS_COUNT)
        return;

    psh = &ga_shots[i];

    static float tvx = 0.f;
    static float tvy = 0.f;
    static float vl  = 0.f;

    psh->p1.x   = gTurret.gun.pos_e.x;
    psh->p1.y   = gTurret.gun.pos_e.y;
    psh->angle  = gTurret.gun.angle;
    psh->lenght = SHOT_INIT_LENGHT;

    psh->p2.x  = psh->p1.x + psh->lenght * rcos(psh->angle);
    psh->p2.y  = psh->p1.y + psh->lenght * rsin(psh->angle);

    tvx = psh->p2.x - psh->p1.x;
    tvy = psh->p2.y - psh->p1.y;

    vl = sqrt(tvx*tvx + tvy*tvy);

    psh->dx = (tvx / vl) * psh->speed;
    psh->dy = (tvy / vl) * psh->speed;

    psh->is_live = 1;
}
//------------------------------------------------------------------------------
void shot_doing()
{
    static unsigned i = 0;

    static unsigned check_i = 0;
    static unsigned col_i   = 0;
    static sShot *psh       = 0;
    static sUnits *gpUnit   = 0;
    i = 0;

    while(i < SHOTS_COUNT)
    {
        psh = &ga_shots[i];

        if(psh->is_live == 1)
        {
            if(psh->lenght < SHOT_LENGHT)
            {
                psh->p2.x = psh->p1.x + psh->lenght * rcos(gTurret.gun.angle);
                psh->p2.y = psh->p1.y + psh->lenght * rsin(gTurret.gun.angle);

                psh->lenght += 3.5;
            }
            else
            {
                psh->p1.x += psh->dx;
                psh->p2.x += psh->dx;
                psh->p1.y += psh->dy;
                psh->p2.y += psh->dy;

                if(psh->p1.x < 0.f || psh->p1.x > SCREEN_WIDTH || psh->p1.y < 0.f)
                    psh->is_live = 0;
                else
                {
                    if(psh->p2.x < 0.0f)
                        continue;

                    check_i = (unsigned)psh->p2.x / COLUMNS_WIDTH;

                    for(col_i = 0; col_i < PAR_COUNT_ON_COLUMN; ++col_i)
                    {
                        gpUnit = &paratrooper_brolly_array[check_i][col_i];
                        if(gpUnit->pos.y > 0)
                        {
                            if(is_unit_cross(&psh->p2, gpUnit) == 1)
                            {
                                gpUnit->pos.y = -1;
                                --parr_brolly_count[check_i];
                            }
                        }
                    }
                }
            }
        }
        ++i;
    }
}
//------------------------------------------------------------------------------
void shot_draw()
{
    static unsigned i = 0;
    static sShot *psh = 0;
    i = 0;

    glColor3ub(254, 0, 0);
    glLineWidth(1);
    glBegin(GL_LINES);
    while(i < SHOTS_COUNT)
    {
        psh = &ga_shots[i];

        if(psh->is_live == 1)
        {
            glVertex2i(psh->p1.x, psh->p1.y);
            glVertex2i(psh->p2.x, psh->p2.y);
        }
        ++i;
    }
    glEnd();
}
//------------------- PRE CALCULATION ------------------------------------------
void pre_calculate()
{
    for(int i = 0; i <= 360; ++i)
    {
        rad_sin[i] = sinf((M_PI * i)/180.f);
        rad_cos[i] = cosf((M_PI * i)/180.f);
    }
}
//------------------------------------------------------------------------------
float rcos(int aAngle)
{
    return rad_cos[aAngle];
}
//------------------------------------------------------------------------------
float rsin(int aAngle)
{
    return rad_sin[aAngle];
}

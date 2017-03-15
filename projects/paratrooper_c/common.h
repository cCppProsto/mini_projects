#ifndef COMMON_H
#define COMMON_H

#define M_PI 3.1415926f

#define SCREEN_WIDTH        640
#define SCREEN_HEIGHT       480
#define IS_FULL_SCREEN      0

#define TURRET_BASE_INIT_X  295
#define TURRET_BASE_INIT_Y  450
#define TURRET_BASE_WIDTH   50
#define TURRET_BASE_HEIGHT  48
#define GUN_LENGHT          30

#define TROOPER_W           8
#define TROOPER_H           16
#define TROOPER_BROLLY_W    24
#define TROOPER_BROLLY_H    44

#define HELICOPTER_W        46
#define HELICOPTER_H        20
#define HELICOPTER_DX       2

#define HELICOPTER_INIT_X_R SCREEN_WIDTH  - HELICOPTER_W
#define HELICOPTER_INIT_Y_R 10
#define HELICOPTER_INIT_X_L 0
#define HELICOPTER_INIT_Y_L (HELICOPTER_H << 1) + 10

#define COLUMNS_COUNT       16
#define COLUMNS_WIDTH       40
#define PAR_COUNT_ON_COLUMN 4

#define SHOTS_COUNT      5
#define SHOT_INIT_LENGHT 1.f
#define SHOT_LENGHT      20.f
#define SHOT_SPEED       5.f

typedef enum
{
    TROOPER         = 0
   ,TROOPER_BROLLY
}eUnitType;

typedef enum
{
    HELICOPTER_LEFT = 0
   ,HELICOPTER_RIGHT
}eHelDirection;

typedef enum
{
    LEFT
   ,RIGHT
}eGunRotate;
//------------------------------------------------------------------------------

typedef struct
{
    int x;
    int y;
}sPos;

typedef struct
{
    float x;
    float y;
}sfPos;

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}sColor;

typedef struct
{
    sPos      pos;
    eUnitType type;
}sUnits;

typedef struct
{
    sPos          pos;
    eHelDirection direction;
    unsigned      isGenerate;
}sHelicopter;

typedef struct
{
          sfPos p1;
          sfPos p2;
          int   angle;
          float dx;
          float dy;
          float lenght;
    const float speed;
          int   is_live;
}sShot;

//--------------------- GUN TURRET ---------------------------------------------
typedef struct
{
    int     angle;
    sPos    pos_s;
    sPos    pos_e;
    sColor  color;
}sGun;

typedef struct
{
    sPos   ltpos;
    sPos   rbpos;
    sColor color;
}sTower;

typedef struct
{
    sPos   ltpos;
    sPos   rbpos;
    sColor color;
}sBase;

typedef struct
{
    sGun   gun;
    sTower tower;
    sBase  base;
}sGunTurret;
//------------------------------------------------------------------------------

#endif // COMMON_H

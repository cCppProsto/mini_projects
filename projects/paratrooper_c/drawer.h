#ifndef UNITS_H
#define UNITS_H

#include "common.h"

void unit_draw(sUnits const *);
void helicopter_draw(sHelicopter const *);
void turret_draw(sGunTurret const *);

unsigned is_unit_cross(sfPos const*, sUnits const*);

#endif // UNITS_H

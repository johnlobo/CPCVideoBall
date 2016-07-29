#ifndef _ENTITIES_H_
#define _ENTITIES_H_

#include <types.h>

struct {
    u16 x,y;
    u8 angle;
    u16 speed;
}TPhysics;

struct {
    TPhysics ph;
    u8 x,y,px,py;
    u8 moved;
}TPlayer;

#endif

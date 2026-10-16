#include "shared/entity.h"
#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/dir_step.h"


/* 16.16 fixed-point coordinate: the whole part is the high halfword. */




/* The effect record the callback runs on (the object header precedes it). */


/* Update position, reduce movement speed, and flag completion when speed runs out. */
void dungeonAdvanceEffectMotionAndSpeed(MotionRecord *motion, EntityRec *position)
{
    s16 next_speed;
    u16 update_count = D_80027452[0];
    u16 z = position->z.w.i;
    u16 x = position->x.w.i;
    u16 y = position->y.w.i;

    D_80027452[0] = update_count + 1;
    if (position->z.w.i < (s16)func_800BCB04(x, y, z + 2)) {
        position->x.v -= (dirStepX[motion->direction] * motion->speed) << 11;
        position->y.v -= (dirStepY[motion->direction] * motion->speed) << 11;
        position->z.v += (0xC0 - motion->speed) << 10;
    }

    next_speed = (u16)motion->speed - 8;
    motion->speed = next_speed;
    if ((next_speed << 16) <= 0) {
        ((ObjectNodeHeader *)motion - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}


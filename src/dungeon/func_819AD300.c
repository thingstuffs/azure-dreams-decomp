#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/dir_step.h"


/* 16.16 fixed-point coordinate: the whole part is the high halfword. */




/* The effect record the callback runs on (the object header precedes it). */


/* Update position, reduce movement speed, and flag completion when speed runs out. */
void func_80024B00(MotionRecord *motion, FixedEffectPosition *position)
{
    s16 next_speed;
    u16 update_count = D_80027452[0];
    u16 z = position->z.part.whole;
    u16 x = position->x.part.whole;
    u16 y = position->y.part.whole;

    D_80027452[0] = update_count + 1;
    if (position->z.part.whole < (s16)func_800BCB04(x, y, z + 2)) {
        position->x.fixed -= (dirStepX[motion->direction] * motion->speed) << 11;
        position->y.fixed -= (dirStepY[motion->direction] * motion->speed) << 11;
        position->z.fixed += (0xC0 - motion->speed) << 10;
    }

    next_speed = (u16)motion->speed - 8;
    motion->speed = next_speed;
    if ((next_speed << 16) <= 0) {
        ((ObjectNodeHeader *)motion - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}


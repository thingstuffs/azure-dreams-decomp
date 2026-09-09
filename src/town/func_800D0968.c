#include "common.h"

typedef struct {
    u8 pad0[0x6C];
    u16 timer;
    u8 pad6E[0x22];
    s16 transition;
} Object;

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
} Position;

typedef struct {
    u8 pad[8];
    Position *target;
} TownState;

extern TownState D_80083498;
extern void func_800CE9EC(Object *, Position *, s32);

void func_800CE0C8(Object *object, Position *position, s32 arg2)
{
    s32 adjusted_y;
    s16 timer;

    timer = (u16)object->timer - 1;
    object->timer = timer;
    if (timer <= 0) {
        object->transition = 1;
        func_800CE9EC(object, position, arg2);
    }

    position->x += (-position->x + D_80083498.target->x) / 2;
    adjusted_y = position->y;
    adjusted_y -= 0x10;
    position->y += (D_80083498.target->y - adjusted_y) / 2;
    position->z += (-position->z + D_80083498.target->z) / 2;
}

/* MECHANISM: Typed Object/Position/TownState fields preserve the 0x18 frame,
   $s0-held position, $a0 global base, and fresh target reloads after stores.
   A separate s32 adjusted_y keeps addiu $v1,-0x10 in the target load-delay slot. */

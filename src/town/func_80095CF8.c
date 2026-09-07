#include "common.h"

typedef struct Vec3i {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct PositionLink {
    s8 pad0[8];
    Vec3i *position;
} PositionLink;

typedef struct TownState {
    u8 pad0[0x10];
    PositionLink *link;
} TownState;

typedef struct TownObject {
    u8 pad0[0xA];
    s16 timer;
} TownObject;

extern TownState D_800CFCB4;
extern void func_80094834(TownObject *, Vec3i *, void *);

void func_80093458(TownObject *object, Vec3i *position, void *arg2)
{
    position->x = (D_800CFCB4.link->position->x + position->x) / 2;
    position->y = (D_800CFCB4.link->position->y + position->y) / 2;
    position->z = (D_800CFCB4.link->position->z + position->z) / 2;

    if (--object->timer < 0) {
        func_80094834(object, position, arg2);
    }
}

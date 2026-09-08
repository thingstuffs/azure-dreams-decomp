#include "common.h"

typedef struct {
    u32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[2];
} LocalVec;

extern s16 func_8008C984();
extern s32 D_800D040C[];
extern s32 D_800FE5D4[];

/* Query the position after subtracting the global Z offset. */
s16 func_80096788(Vec3i *position) {
    LocalVec pos;

    pos.x = position->x;
    pos.y = position->y;
    pos.z = position->z - D_800FE5D4[0];
    return func_8008C984(&pos, D_800D040C[0], 4);
}

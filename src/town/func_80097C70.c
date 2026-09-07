#include "common.h"

typedef struct TownMoveInner {
    s32 unk0[3];
    s32 x;
    s32 y;
    s32 z;
} TownMoveInner;

typedef struct TownMoveMiddle {
    s32 unk0[2];
    TownMoveInner *inner;
} TownMoveMiddle;

typedef struct TownMoveGlobal {
    s32 unk0[8];
    TownMoveMiddle *middle;
    u8 unk24[0x17];
    u8 enabled;
} TownMoveGlobal;

typedef struct TownMoveOut {
    s32 x;
    s32 y;
    s32 z;
} TownMoveOut;

extern TownMoveGlobal D_800CFCB4;

void func_800953D0(TownMoveOut *out) {
    s32 z;

    if (D_800CFCB4.enabled != 0) {
        out->x += D_800CFCB4.middle->inner->x;
        out->y += D_800CFCB4.middle->inner->y;
        z = D_800CFCB4.middle->inner->z;
        if (z > 0) {
            out->z += z;
        }
    }
}

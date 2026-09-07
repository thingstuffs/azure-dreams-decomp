#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} DungeonState;

extern s32 func_800A2BDC(void *arg0);
extern DungeonState D_80083460;
extern s16 D_800DCF5E;
extern u8 D_801751C0[12];

void func_801751C0(void *arg0, s32 arg1, s32 arg2, void *arg3)
{
    u8 *entity = arg0;
    u8 *other = arg3;
    DungeonState *state = &D_80083460;
    s32 kind = 0x18;

    other[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = &D_801751C0;
    entity[0x9A] = kind;
    entity[0x9B] = 0;
    other[0x6D] = 0;
    if (!(state->flags & 0x2000) && ((func_800A2BDC(other) << 16) == 0)) {
        *(void **)(entity + 0x8C) = 0;
        entity[0x9A] = kind;
        entity[0x9B] = 0;
        D_800DCF5E = 0;
        state->count++;
    }
}

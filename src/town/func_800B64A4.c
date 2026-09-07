#include "common.h"

typedef struct TownState {
    u8 pad0[8];
    s32 enabled;
    u8 padC[4];
    s32 flags;
} TownState;

extern TownState D_80083160;

s32 func_800B3C04(s32 *arg0)
{
    s32 choice;
    s32 flags;
    s32 store_value;
    TownState *base;

    base = &D_80083160;
    choice = -1;
    if (base->enabled != 0) {
        flags = base->flags;
        if (flags & 0x40) {
            choice = 2;
            goto selected;
        }
        if (flags & 0x10) {
            choice = 3;
            goto selected;
        }
        if (flags & 0x20) {
            choice = 4;
        }
    }
selected:
    store_value = 4;
    if (choice != -1) {
        arg0[choice + 3] = store_value;
    }
    return choice;
}

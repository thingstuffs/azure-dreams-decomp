#include "common.h"

typedef struct {
    u8 x;
    u8 y;
    s8 pad[10];
} DungeonPosition;

typedef struct {
    u8 unk0;
    u8 active;
    u8 pad[2];
} DungeonStatus;

extern DungeonPosition D_800E36C8[64];
extern DungeonStatus D_800E3548[64];

/* Returns whether an active slot other than the excluded slot occupies (x, y). */
s32 func_8001E110(s32 excluded_slot, s16 x, s16 y)
{
    s32 slot;

    for (slot = 0; slot < 64; slot++) {
        if ((excluded_slot != slot) &&
            (D_800E3548[slot].active != 0) &&
            (D_800E36C8[slot].x == x) &&
            (D_800E36C8[slot].y == y)) {
            return 1;
        }
    }
    return 0;
}

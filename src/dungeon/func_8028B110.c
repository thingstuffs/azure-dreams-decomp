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

s32 func_8001E110(s32 excluded, s16 x, s16 y)
{
    s32 i;

    for (i = 0; i < 64; i++) {
        if ((excluded != i) &&
            (D_800E3548[i].active != 0) &&
            (D_800E36C8[i].x == x) &&
            (D_800E36C8[i].y == y)) {
            return 1;
        }
    }
    return 0;
}

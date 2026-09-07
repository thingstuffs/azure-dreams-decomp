#include "common.h"

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 pad;
} DungeonColor;

typedef struct {
    DungeonColor color[8];
    u8 pad_20[0x3A];
    s16 remaining;
    s16 duration;
} DungeonColorWork;

extern s16 D_80025B60;
extern s32 D_800814A0;

void func_800246C4(DungeonColorWork *work)
{
    s16 i;
    DungeonColor *color;

    D_80025B60 = 1;
    work->remaining--;

    for (i = 0; i < 4; i++) {
        color = &work->color[i];
        color->r = (color[4].r * work->remaining) / work->duration;
        color->g = (color[4].g * work->remaining) / work->duration;
        color->b = (color[4].b * work->remaining) / work->duration;
    }

    if (work->remaining <= 0) {
        *(u16 *)((u8 *)work - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

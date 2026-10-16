#include "modules/dungeon_ovl_7e6e1800.h"

void dungeonFadeFourColorsToBlack(Row_81922EC4_DungeonColorWork *work)
{
    s16 color_index;
    Row_81922EC4_DungeonColor *color;

    (*(s16 *)D_80025B60) = 1;
    work->remaining--;

    for (color_index = 0; color_index < 4; color_index++) {
        color = &work->color[color_index];
        color->r = (color[4].r * work->remaining) / work->duration;
        color->g = (color[4].g * work->remaining) / work->duration;
        color->b = (color[4].b * work->remaining) / work->duration;
    }

    if (work->remaining <= 0) {
        *(u16 *)((u8 *)work - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

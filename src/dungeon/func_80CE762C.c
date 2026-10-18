#include "modules/dungeon_ovl_7f469800_p01.h"

/* Advance the RGB fade toward black and set completion flags when it ends. */
void update_saved_rgb_fade(T_80170E2C_FadeState *fade, s32 unused, T_80170E2C_FadeOutput *output)
{
    s16 remaining;

    remaining = fade->remaining - 1;
    fade->remaining = remaining;
    output->red = (fade->red * remaining) / fade->divisor;
    output->green = (fade->green * (s16)fade->remaining) / fade->divisor;
    output->blue = (fade->blue * (s16)fade->remaining) / fade->divisor;

    if ((s16)fade->remaining <= 0) {
        *(u16 *)((u8 *)fade - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

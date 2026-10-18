#include "common.h"
#include "shared/object_flags.h"


/* Fade the primitive as the effect countdown expires, then set completion flags. */
void advance_actor_replacement_sequence(void *effect, s32 unused, void *primitive)
{
    s16 ticks_left;

    ticks_left = *(s16 *)((u8 *)effect + 0x96);
    if (ticks_left < 16) {
        s8 shade = ticks_left * 3;

        *(s8 *)((u8 *)primitive + 0xE) = shade;
        *(s8 *)((u8 *)primitive + 0xD) = shade;
        *(s8 *)((u8 *)primitive + 0xC) = shade;
    } else {
        *(s32 *)((u8 *)primitive + 0xC) = 0x808080;
    }
    ticks_left = *(u16 *)((u8 *)effect + 0x96) - 1;
    *(s16 *)((u8 *)effect + 0x96) = ticks_left;
    if (ticks_left <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_flags.h"

/* Dims all three color channels and shrinks the effect, marking it for removal when brightness runs out. */
void fade_effect_and_mark_cleanup(void *record, s32 unused, void *effect) {
    s32 intensity;
    u16 size;

    intensity = *((u8 *)effect + 0xE);
    intensity -= 0x10;
    if (intensity < 0) {
        *(u16 *)((u8 *)record - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    *((u8 *)effect + 0xE) = intensity;
    *((u8 *)effect + 0xD) = intensity;
    *((u8 *)effect + 0xC) = intensity;
    size = *(u16 *)((u8 *)effect + 0x20) - 0x100;
    *(u16 *)((u8 *)effect + 0x20) = size;
    *(u16 *)((u8 *)effect + 0x1E) = size;
    *(u16 *)((u8 *)effect + 0x1C) = size;
}

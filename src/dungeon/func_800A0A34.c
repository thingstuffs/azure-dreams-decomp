#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/object_flags.h"


/* Advance the timed ramp to 255 and update completion and shutdown flags. */
void func_800A6194(void *ramp) {
    u16 ticks_left;
    u32 initial_flags;
    u32 current_flags;

    ticks_left = *(u16 *)((s8 *)ramp + 8) - 1;
    *(u16 *)((s8 *)ramp + 8) = ticks_left;
    if ((s16)ticks_left > 0) {
        *(s16 *)((s8 *)ramp + 10) += (0xFF - *(s16 *)((s8 *)ramp + 10)) / (s16)ticks_left;
    } else {
        *(s16 *)((s8 *)ramp + 10) = 0xFF;
        initial_flags = ((u32)D_800E296C);
        *(u16 *)((s8 *)ramp + 8) = 0;
        D_800E296C = initial_flags | 0x02000000;
    }
    current_flags = (u32) D_800E296C;
    if (!(current_flags & 0x01000000)) {
        D_800E296C = current_flags & 0xFDFFFFFF;
        *(s16 *)((s8 *)ramp - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

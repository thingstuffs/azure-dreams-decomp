#include "modules/dungeon_ovl_183a800.h"
#include "common.h"
#include "shared/object_flags.h"


/* Advances the timer, ramps target values, and flags completion on timeout or target status. */
void func_80024B14(void *state_data, s32 unused, void *target) {
    u16 timer;
    u8 *state = state_data;

    timer = *(u16 *)(state + 2) + 2;
    D_80025914 = 1;
    *(u16 *)(state + 2) = timer;
    if ((s16)timer < 40) {
        *(s16 *)((u8 *)target + 0x1C) = (s16)timer * 204;
        *(s16 *)((u8 *)target + 0x1E) =
            (s16)*(u16 *)(state + 2) * 204;
    }
    if ((s16)*(u16 *)(state + 2) >= 120) {
        *(u16 *)(state - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
    if (*(u16 *)((u8 *)target + 0x14) & 0x8000) {
        *(u16 *)(state - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

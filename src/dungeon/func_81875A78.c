#include "modules/dungeon_native_abi.h"
#include "modules/dungeon_ovl_1894800.h"
#include "common.h"
#include "shared/object_flags.h"



/* Adjust height conditionally and set flags when the countdown reaches zero or below. */
void func_80025278(void *state, s16 *position)
{
    s16 *state_words = state;
    s16 countdown;

    D_80026664 = 1;
    if (position[5] < (s16)func_800BCB04((u16)position[1], (u16)position[3], position[5] + 2)) {
        ((s32 *)position)[2] += *(s32 *)((u8 *)state + 0x48);
    }

    countdown = (u16)state_words[25] - 4;
    state_words[25] = countdown;
    if ((countdown << 16) <= 0) {
        ((u16 *)state_words)[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

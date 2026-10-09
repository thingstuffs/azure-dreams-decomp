/* Selector 59, retail file [0x1990FE8, 0x19910A8); complete callable clone. */
#include "common.h"
#include "shared/object_flags.h"
#include "modules/dungeon_native_abi.h"

extern s16 D_80025FF4;


/* Adjust height conditionally and set flags when the countdown reaches zero or below. */
void func_800247E8(void *state, s16 *position)
{
    s16 *state_words = state;
    s16 countdown;

    D_80025FF4 = 1;
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

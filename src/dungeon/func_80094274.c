#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad_0[8];
    s32 field_8;
    u8 pad_C[4];
    s16 field_10;
} S_80094274;

/* Advance the counter and set completion flags when the countdown expires. */
void func_800999D4(S_80094274 *state)
{
    state->field_8++;
    if (--state->field_10 <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

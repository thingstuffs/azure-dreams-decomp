#include "common.h"

typedef struct {
    u8 pad_0[8];
    s32 field_8;
    u8 pad_C[4];
    s16 field_10;
} S_80094274;

typedef struct {
    s32 value;
    s32 pad[2];
} S_800814A0;

extern S_800814A0 D_800814A0;

/* Advance the counter and set completion flags when the countdown expires. */
void func_800999D4(S_80094274 *state)
{
    state->field_8++;
    if (--state->field_10 <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }
}

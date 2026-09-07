#include "common.h"

typedef struct {
    u8 pad00[0x11];
    u8 unk11;
    u8 pad12[0x6];
    s32 unk18;
} S_80043868;

extern s32 func_8004383C(S_80043868 *arg0, s16 arg1);

/* Scales the current value between two bounds, capping the result at 20. */
s32 func_80043868(S_80043868 *state)
{
    s32 lower;
    s32 upper;
    register s32 range ASM_REG("$4");   /* MATCH pin: slus-diff */
    register s32 scaled_value ASM_REG("$4");   /* MATCH pin: slus-diff */

    lower = func_8004383C(state, -1);
    upper = func_8004383C(state, 0);
    range = upper - lower;
    lower = state->unk18 - lower;
    scaled_value = (lower * 20) / range;
    if (scaled_value >= 21) {
        scaled_value = 20;
    }
    return scaled_value;
}

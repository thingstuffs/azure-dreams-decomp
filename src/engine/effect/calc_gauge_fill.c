#include "common.h"

typedef struct {
    u8 pad00[0x11];
    u8 unk11;
    u8 pad12[0x6];
    s32 unk18;
} S_80043868;

extern s32 lookup_level_experience_threshold(S_80043868 *entry, s16 index_offset);

/* Scales the current value between two bounds, capping the result at 20. */
s32 calc_gauge_fill(S_80043868 *state)
{
    s32 lower;
    s32 upper;
    s32 range;

    lower = lookup_level_experience_threshold(state, -1);
    upper = lookup_level_experience_threshold(state, 0);
    range = upper - lower;
    lower = state->unk18 - lower;
    range = (lower * 20) / range;
    if (range >= 21) {
        range = 20;
    }
    return range;
}

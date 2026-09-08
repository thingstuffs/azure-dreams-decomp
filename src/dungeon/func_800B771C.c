#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BCE7C_0 {
    u8 pad_00[0x154];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_154;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_158;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_15C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_160;   /* overlapping accesses */
    s32 unk_164;
    s32 unk_168;
    s32 unk_16C;
    s32 unk_170;
    u8 pad_174[0x4];
    s32 unk_178;
    s32 unk_17C;
    s32 unk_180;
} S_800BCE7C_0;   /* arg0 in func_800BCE7C */


s32 func_80065F90();

/* Compute direction angles and check that adjacent angular gaps do not exceed a half turn. */
s32 func_800BCE7C(S_800BCE7C_0 *state) {
    s32 second_offset;
    s32 fourth_angle;
    s32 fourth_offset;
    s32 third_angle;
    s32 third_offset;
    s32 second_angle;
    s32 second_to_third;
    s32 fourth_to_first;
    s32 third_to_fourth;

    if (state->unk_154.at00.v != 0) {
        if (state->unk_160.at00.v == 0) {
            goto accept;
        }
        state->unk_164 = func_80065F90(state->unk_154.at02.v, (s16) state->unk_154.at00.v);
        fourth_angle = func_80065F90(state->unk_160.at02.v, (s16) state->unk_160.at00.v);
        state->unk_170 = fourth_angle;
        fourth_offset = fourth_angle - state->unk_164;
        fourth_to_first = (0x1000 - fourth_offset) & 0xFFF;
        state->unk_180 = fourth_to_first;
        state->unk_170 = fourth_offset;
        if (fourth_to_first >= 0x801) {
            return 0;
        }
        if (state->unk_15C.at00.v == 0) {
            goto accept;
        }
        third_angle = func_80065F90(state->unk_15C.at02.v, (s16) state->unk_15C.at00.v);
        state->unk_16C = third_angle;
        third_offset = third_angle - state->unk_164;
        third_to_fourth = (state->unk_170 - third_offset) & 0xFFF;
        state->unk_17C = third_to_fourth;
        state->unk_16C = third_offset;
        if (third_to_fourth >= 0x801) {
            return 0;
        }
        if (state->unk_158.at00.v != 0) {
            goto check_second;
        }
accept:
        ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        return 1;
check_second:
        second_angle = func_80065F90(state->unk_158.at02.v, (s16) state->unk_158.at00.v);
        state->unk_168 = second_angle;
        second_offset = (second_angle - state->unk_164) & 0xFFF;
        state->unk_168 = second_offset;
        if (second_offset < 0x801) {
            second_to_third = (state->unk_16C - second_offset) & 0xFFF;
            state->unk_178 = second_to_third;
            return second_to_third < 0x801;
        }
        return 0;
    }
    return 1;
}

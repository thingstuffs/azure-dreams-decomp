#include "common.h"

typedef union Quad {
    u32 words[4];
    s16 vals[8];
} Quad;

typedef struct ScratchQuad {
    u8 pad00[0x6C];
    Quad quad;
    s32 angle0;
    s32 angle1;
    s32 angle2;
    s32 angle3;
    u8 pad8C[4];
    s32 diff1;
    s32 diff2;
    s32 diff3;
} ScratchQuad;

extern s32 func_80065F90(s16, s16);

/* Checks the quad's angular gaps against a half-turn limit. */
s32 func_8008CE08(ScratchQuad *scratch) {
    if (scratch->quad.words[0] == 0) {
        return 1;
    }
    if (scratch->quad.words[3] == 0) {
        goto return_one;
    }

    scratch->angle0 = func_80065F90(scratch->quad.vals[1], scratch->quad.vals[0]);
    scratch->angle3 = func_80065F90(scratch->quad.vals[7], scratch->quad.vals[6]);
    scratch->angle3 -= scratch->angle0;
    scratch->diff3 = (4096 - scratch->angle3) & 0xFFF;
    if (scratch->diff3 >= 2049) {
        return 0;
    }
    if (scratch->quad.words[2] == 0) {
        goto return_one;
    }

    scratch->angle2 = func_80065F90(scratch->quad.vals[5], scratch->quad.vals[4]);
    scratch->angle2 -= scratch->angle0;
    scratch->diff2 = (scratch->angle3 - scratch->angle2) & 0xFFF;
    if (scratch->diff2 >= 2049) {
        return 0;
    }
    if (scratch->quad.words[1] != 0) {
        goto have_angle1;
    }

return_one:
    return 1;

have_angle1:
    scratch->angle1 = func_80065F90(scratch->quad.vals[3], scratch->quad.vals[2]);
    scratch->angle1 = (scratch->angle1 - scratch->angle0) & 0xFFF;
    if (scratch->angle1 >= 2049) {
        return 0;
    }
    scratch->diff1 = (scratch->angle2 - scratch->angle1) & 0xFFF;
    return scratch->diff1 < 2049;
}

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

s32 func_8008CE08(ScratchQuad *arg0) {
    if (arg0->quad.words[0] == 0) {
        return 1;
    }
    if (arg0->quad.words[3] == 0) {
        goto return_one;
    }

    arg0->angle0 = func_80065F90(arg0->quad.vals[1], arg0->quad.vals[0]);
    arg0->angle3 = func_80065F90(arg0->quad.vals[7], arg0->quad.vals[6]);
    arg0->angle3 -= arg0->angle0;
    arg0->diff3 = (4096 - arg0->angle3) & 0xFFF;
    if (arg0->diff3 >= 2049) {
        return 0;
    }
    if (arg0->quad.words[2] == 0) {
        goto return_one;
    }

    arg0->angle2 = func_80065F90(arg0->quad.vals[5], arg0->quad.vals[4]);
    arg0->angle2 -= arg0->angle0;
    arg0->diff2 = (arg0->angle3 - arg0->angle2) & 0xFFF;
    if (arg0->diff2 >= 2049) {
        return 0;
    }
    if (arg0->quad.words[1] != 0) {
        goto have_angle1;
    }

return_one:
    return 1;

have_angle1:
    arg0->angle1 = func_80065F90(arg0->quad.vals[3], arg0->quad.vals[2]);
    arg0->angle1 = (arg0->angle1 - arg0->angle0) & 0xFFF;
    if (arg0->angle1 >= 2049) {
        return 0;
    }
    arg0->diff1 = (arg0->angle2 - arg0->angle1) & 0xFFF;
    return arg0->diff1 < 2049;
}

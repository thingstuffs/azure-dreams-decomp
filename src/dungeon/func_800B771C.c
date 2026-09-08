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

s32 func_800BCE7C(S_800BCE7C_0 *arg0) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;

    if (arg0->unk_154.at00.v != 0) {
        if (arg0->unk_160.at00.v == 0) {
            goto block_6;
        }
        arg0->unk_164 = func_80065F90(arg0->unk_154.at02.v, (s16) arg0->unk_154.at00.v);
        temp_v0 = func_80065F90(arg0->unk_160.at02.v, (s16) arg0->unk_160.at00.v);
        arg0->unk_170 = temp_v0;
        temp_v0_2 = temp_v0 - arg0->unk_164;
        temp_v1_2 = (0x1000 - temp_v0_2) & 0xFFF;
        arg0->unk_180 = temp_v1_2;
        arg0->unk_170 = temp_v0_2;
        if (temp_v1_2 >= 0x801) {
            return 0;
        }
        if (arg0->unk_15C.at00.v == 0) {
            goto block_6;
        }
        temp_v0_3 = func_80065F90(arg0->unk_15C.at02.v, (s16) arg0->unk_15C.at00.v);
        arg0->unk_16C = temp_v0_3;
        temp_v0_4 = temp_v0_3 - arg0->unk_164;
        temp_v1_3 = (arg0->unk_170 - temp_v0_4) & 0xFFF;
        arg0->unk_17C = temp_v1_3;
        arg0->unk_16C = temp_v0_4;
        if (temp_v1_3 >= 0x801) {
            return 0;
        }
        if (arg0->unk_158.at00.v != 0) {
            goto block_7;
        }
block_6:
        ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        return 1;
block_7:
        temp_v0_5 = func_80065F90(arg0->unk_158.at02.v, (s16) arg0->unk_158.at00.v);
        arg0->unk_168 = temp_v0_5;
        temp_a0 = (temp_v0_5 - arg0->unk_164) & 0xFFF;
        arg0->unk_168 = temp_a0;
        if (temp_a0 < 0x801) {
            temp_v1 = (arg0->unk_16C - temp_a0) & 0xFFF;
            arg0->unk_178 = temp_v1;
            return temp_v1 < 0x801;
        }
        return 0;
    }
    return 1;
}

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

/* True unless the quad's corner angles are laid out so that one of its successive turns exceeds half a revolution. */
s32 func_800BCE7C(S_800BCE7C_0 *poly) {
    s32 delta_3;
    s32 angle_1;
    s32 delta_1;
    s32 angle_2;
    s32 delta_2;
    s32 angle_3;
    s32 turn_1;
    s32 turn_2;
    s32 turn_3;

    if (poly->unk_154.at00.v == 0) {
        return 1;
    }
    if (poly->unk_160.at00.v == 0) {
        return 1;
    }
    poly->unk_164 = func_80065F90(poly->unk_154.at02.v, (s16) poly->unk_154.at00.v);
    angle_1 = func_80065F90(poly->unk_160.at02.v, (s16) poly->unk_160.at00.v);
    poly->unk_170 = angle_1;
    delta_1 = angle_1 - poly->unk_164;
    turn_1 = (0x1000 - delta_1) & 0xFFF;
    poly->unk_180 = turn_1;
    poly->unk_170 = delta_1;
    if (turn_1 >= 0x801) {
        return 0;
    }
    if (poly->unk_15C.at00.v == 0) {
        return 1;
    }
    angle_2 = func_80065F90(poly->unk_15C.at02.v, (s16) poly->unk_15C.at00.v);
    poly->unk_16C = angle_2;
    delta_2 = angle_2 - poly->unk_164;
    turn_2 = (poly->unk_170 - delta_2) & 0xFFF;
    poly->unk_17C = turn_2;
    poly->unk_16C = delta_2;
    if (turn_2 >= 0x801) {
        return 0;
    }
    if (poly->unk_158.at00.v == 0) {
        return 1;
    }
    angle_3 = func_80065F90(poly->unk_158.at02.v, (s16) poly->unk_158.at00.v);
    poly->unk_168 = angle_3;
    delta_3 = (angle_3 - poly->unk_164) & 0xFFF;
    poly->unk_168 = delta_3;
    if (delta_3 >= 0x801) {
        return 0;
    }
    turn_3 = (poly->unk_16C - delta_3) & 0xFFF;
    poly->unk_178 = turn_3;
    return turn_3 < 0x801;
}


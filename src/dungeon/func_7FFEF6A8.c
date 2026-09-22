#include "common.h"
#include "m2c_compat.h"

typedef struct S_7FFEF6A8_0 {
    u8 pad_00[0x6C];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_6C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_70;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_74;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_78;   /* overlapping accesses */
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    u8 pad_8C[0x4];
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
} S_7FFEF6A8_0;   /* poly in func_8008CE08 */


s32 func_80065F90();                        /* extern */

/* True unless the quad's corner angles are laid out so that one of its successive turns exceeds half a revolution. */
s32 func_8008CE08(S_7FFEF6A8_0 *poly) {
    s32 delta_3;
    s32 angle_1;
    s32 delta_1;
    s32 angle_2;
    s32 delta_2;
    s32 angle_3;
    s32 turn_1;
    s32 turn_2;
    s32 turn_3;

    if (poly->unk_6C.at00.v == 0) {
        return 1;
    }
    if (poly->unk_78.at00.v == 0) {
        goto tail_one;
    }
    poly->unk_7C = func_80065F90(poly->unk_6C.at02.v, (s16) poly->unk_6C.at00.v);
    angle_1 = func_80065F90(poly->unk_78.at02.v, (s16) poly->unk_78.at00.v);
    poly->unk_88 = angle_1;
    delta_1 = angle_1 - poly->unk_7C;
    turn_1 = (0x1000 - delta_1) & 0xFFF;
    poly->unk_98 = turn_1;
    poly->unk_88 = delta_1;
    if (turn_1 >= 0x801) {
        return 0;
    }
    if (poly->unk_74.at00.v == 0) {
        goto tail_one;
    }
    angle_2 = func_80065F90(poly->unk_74.at02.v, (s16) poly->unk_74.at00.v);
    poly->unk_84 = angle_2;
    delta_2 = angle_2 - poly->unk_7C;
    turn_2 = (poly->unk_88 - delta_2) & 0xFFF;
    poly->unk_94 = turn_2;
    poly->unk_84 = delta_2;
    if (turn_2 >= 0x801) {
        return 0;
    }
    if (poly->unk_70.at00.v != 0) {
        goto have_field70;
    }
tail_one:
    return 1;
have_field70:
    angle_3 = func_80065F90(poly->unk_70.at02.v, (s16) poly->unk_70.at00.v);
    poly->unk_80 = angle_3;
    delta_3 = (angle_3 - poly->unk_7C) & 0xFFF;
    poly->unk_80 = delta_3;
    if (delta_3 >= 0x801) {
        return 0;
    }
    turn_3 = (poly->unk_84 - delta_3) & 0xFFF;
    poly->unk_90 = turn_3;
    return turn_3 < 0x801;
}

/* MECHANISM: A vars=0 24-byte frame follows from one held object base in s0.
   Guard-clause CFGs retain the two move-zero branch slots and exact store order.
   A pinned a0 angle plus v0 tail result reproduces the final register lifetimes.
   Keeping v0 before the field90 store lets that store fill the noreturn tail-j slot. */

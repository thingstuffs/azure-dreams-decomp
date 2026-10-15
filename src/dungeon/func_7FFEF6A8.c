#include "modules/dungeon_ovl_16b08_f6a8.h"

s32 func_8008CE08(ovl_16b08_f6a8_7FFEF6A8_S_7FFEF6A8_0 *poly) {
    s32 delta_3;
    s32 angle_1;
    s32 delta_1;
    s32 angle_2;
    s32 delta_2;
    s32 angle_3;
    s32 turn_1;
    s32 turn_2;
    s32 turn_3;

    if (poly->ovl_16b08_f6a8_7FFEF6A8_unk_6C.ovl_16b08_f6a8_7FFEF6A8_at00.v == 0) {
        return 1;
    }
    if (poly->ovl_16b08_f6a8_7FFEF6A8_unk_78.ovl_16b08_f6a8_7FFEF6A8_at00.v == 0) {
        return 1;
    }
    poly->unk_7C = func_80065F90(poly->ovl_16b08_f6a8_7FFEF6A8_unk_6C.ovl_16b08_f6a8_7FFEF6A8_at02.v, (s16) poly->ovl_16b08_f6a8_7FFEF6A8_unk_6C.ovl_16b08_f6a8_7FFEF6A8_at00.v);
    angle_1 = func_80065F90(poly->ovl_16b08_f6a8_7FFEF6A8_unk_78.ovl_16b08_f6a8_7FFEF6A8_at02.v, (s16) poly->ovl_16b08_f6a8_7FFEF6A8_unk_78.ovl_16b08_f6a8_7FFEF6A8_at00.v);
    poly->unk_88 = angle_1;
    delta_1 = angle_1 - poly->unk_7C;
    turn_1 = (0x1000 - delta_1) & 0xFFF;
    poly->unk_98 = turn_1;
    poly->unk_88 = delta_1;
    if (turn_1 >= 0x801) {
        return 0;
    }
    if (poly->ovl_16b08_f6a8_7FFEF6A8_unk_74.ovl_16b08_f6a8_7FFEF6A8_at00.v == 0) {
        return 1;
    }
    angle_2 = func_80065F90(poly->ovl_16b08_f6a8_7FFEF6A8_unk_74.ovl_16b08_f6a8_7FFEF6A8_at02.v, (s16) poly->ovl_16b08_f6a8_7FFEF6A8_unk_74.ovl_16b08_f6a8_7FFEF6A8_at00.v);
    poly->unk_84 = angle_2;
    delta_2 = angle_2 - poly->unk_7C;
    turn_2 = (poly->unk_88 - delta_2) & 0xFFF;
    poly->unk_94 = turn_2;
    poly->unk_84 = delta_2;
    if (turn_2 >= 0x801) {
        return 0;
    }
    if (poly->ovl_16b08_f6a8_7FFEF6A8_unk_70.ovl_16b08_f6a8_7FFEF6A8_at00.v == 0) {
        return 1;
    }
    angle_3 = func_80065F90(poly->ovl_16b08_f6a8_7FFEF6A8_unk_70.ovl_16b08_f6a8_7FFEF6A8_at02.v, (s16) poly->ovl_16b08_f6a8_7FFEF6A8_unk_70.ovl_16b08_f6a8_7FFEF6A8_at00.v);
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

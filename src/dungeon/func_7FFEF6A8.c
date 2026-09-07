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
} S_7FFEF6A8_0;   /* arg0 in func_7FFEF6A8 */


s32 func_80065F90();                        /* extern */
void func_8008CF34(void) __attribute__((noreturn)); /* extern */

s32 func_7FFEF6A8(S_7FFEF6A8_0 *arg0) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;

    if (arg0->unk_6C.at00.v == 0) {
        return 1;
    }
    if (arg0->unk_78.at00.v == 0) {
        goto tail_one;
    }
    arg0->unk_7C = func_80065F90(arg0->unk_6C.at02.v, (s16) arg0->unk_6C.at00.v);
    temp_v0 = func_80065F90(arg0->unk_78.at02.v, (s16) arg0->unk_78.at00.v);
    arg0->unk_88 = temp_v0;
    temp_v0_2 = temp_v0 - arg0->unk_7C;
    temp_v1 = (0x1000 - temp_v0_2) & 0xFFF;
    arg0->unk_98 = temp_v1;
    arg0->unk_88 = temp_v0_2;
    if (temp_v1 >= 0x801) {
        return 0;
    }
    if (arg0->unk_74.at00.v == 0) {
        goto tail_one;
    }
    temp_v0_3 = func_80065F90(arg0->unk_74.at02.v, (s16) arg0->unk_74.at00.v);
    arg0->unk_84 = temp_v0_3;
    temp_v0_4 = temp_v0_3 - arg0->unk_7C;
    temp_v1_2 = (arg0->unk_88 - temp_v0_4) & 0xFFF;
    arg0->unk_94 = temp_v1_2;
    arg0->unk_84 = temp_v0_4;
    if (temp_v1_2 >= 0x801) {
        return 0;
    }
    if (arg0->unk_70.at00.v != 0) {
        goto have_field70;
    }
tail_one:
    {
        s32 rv;
        rv = 1;
        ASM_TAILSLOT_PIN(rv);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8008CF34();
        return rv;
    }
have_field70:
    temp_v0_5 = func_80065F90(arg0->unk_70.at02.v, (s16) arg0->unk_70.at00.v);
    arg0->unk_80 = temp_v0_5;
    temp_a0 = (temp_v0_5 - arg0->unk_7C) & 0xFFF;
    arg0->unk_80 = temp_a0;
    if (temp_a0 < 0x801) {
        s32 tail_angle;
        register s32 rv ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

        tail_angle = (arg0->unk_84 - temp_a0) & 0xFFF;
        rv = tail_angle < 0x801;
        ASM_KEEP(rv);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        arg0->unk_90 = tail_angle;
        func_8008CF34();
        return rv;
    }
    return 0;
}

/* MECHANISM: A vars=0 24-byte frame follows from one held object base in s0.
   Guard-clause CFGs retain the two move-zero branch slots and exact store order.
   A pinned a0 angle plus v0 tail result reproduces the final register lifetimes.
   Keeping v0 before the field90 store lets that store fill the noreturn tail-j slot. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80175D54.h"

typedef struct S_8016F5D8_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x26];
    s32 unk_2C;
} S_8016F5D8_0;   /* arg2 in func_8016F5D8 */

typedef struct S_8016F5D8_1 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0xA];
    u16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
} S_8016F5D8_1;   /* arg0 in func_8016F5D8 */

typedef struct S_8016F5D8_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016F5D8_2;   /* arg1 in func_8016F5D8 */



s32 func_800644B8();                        /* extern */
extern M2C_UNK D_80173DA4;
extern M2C_UNK D_80173DB4;
extern u8 *D_80175D54;

void func_8016F5D8(S_8016F5D8_1 *arg0, S_8016F5D8_2 *arg1, S_8016F5D8_0 *arg2) {
    s32 temp_v1;
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 temp_a1;
    s32 temp_a1_3;
    s32 temp_v1_2;
    s16 signed_count;

    temp_v1 = arg2->unk_2C;
    if (temp_v1 == &D_80173DA4) {
        if (arg2->unk_04 == 0x100) {
            arg0->unk_9E = 0U;
            arg0->unk_A0.at00.v = 0;
        }
        if ((u32) ((u8) arg2->unk_04 - 1) < 4U) {
            temp_v1_2 = arg0->unk_9E;
            ASM_KEEP(temp_v1_2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            signed_count = temp_v1_2;
            temp_a0 = signed_count * 0xAA;
            temp_v1_2++;
            arg0->unk_9E = temp_v1_2;
            arg0->unk_A0.at00.v += func_800644B8(temp_a0) << 5;
            goto finish;
        }
        temp_v1_2 = arg0->unk_9E;
        ASM_KEEP(temp_v1_2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        signed_count = temp_v1_2;
        temp_a0 = signed_count * 0xAA;
        temp_v1_2++;
        arg0->unk_9E = temp_v1_2;
        arg0->unk_A0.at00.v += func_800644B8(temp_a0) << 6;
        goto finish;
    }
    if (temp_v1 == &D_80173DB4) {
        if (arg2->unk_04 == 0x100) {
            arg0->unk_9E = 0U;
            arg0->unk_A0.at00.v = 0;
        }
        if ((u32) ((u8) arg2->unk_04 - 1) < 4U) {
            temp_a1 = arg0->unk_9E;
            ASM_KEEP(temp_a1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            signed_count = temp_a1;
            temp_a0 = signed_count * 0x155;
            temp_a1++;
            arg0->unk_9E = temp_a1;
            arg0->unk_A0.at00.v += func_800644B8(temp_a0, temp_a1) << 5;
            goto finish;
        }
        temp_a1_3 = arg0->unk_9E;
        ASM_KEEP(temp_a1_3);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        signed_count = temp_a1_3;
        temp_a0 = signed_count * 0x155;
        temp_a1_3++;
        arg0->unk_9E = temp_a1_3;
        arg0->unk_A0.at00.v += func_800644B8(temp_a0) << 6;
    }
finish:
    arg1->unk_0A = (s16) ((((Rec_D_80175D54 *)D_80175D54)->unk_A8 + arg0->unk_92) - arg0->unk_A0.at02.v);
}

/* MECHANISM: Direct accumulator expressions and one-argument fallback calls recover
   the shared jal/shift/add CFG while arg0/arg1 naturally hold s0/s1 in a 0x20 frame.
   ASM_KEEP preserves each lhu for explicit sign-extension; a guarded $a0 pin plus
   ASM_USE keeps the multiply chain ahead of the in-place counter increment. */

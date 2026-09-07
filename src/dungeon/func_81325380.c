#include "common.h"
#include "m2c_compat.h"

extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_8016CD88() __attribute__((noreturn));
extern void func_8016CDC0() __attribute__((noreturn));
extern void func_8016CE8C() __attribute__((noreturn));
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_8016B778[];
extern u8 D_8017467C[];
extern u8 D_80174684[];

typedef struct S_8016CB80_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
    u8 pad_A4[0xF];
    u8 unk_B3;
} S_8016CB80_0;   /* arg0 in func_8016CB80 */

typedef struct S_8016CB80_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_8016CB80_1;   /* arg3 in func_8016CB80 */

typedef struct S_8016CB80_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { void * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_8016CB80_2;   /* arg2 in func_8016CB80 */

typedef struct S_8016CB80_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016CB80_3;   /* arg1 in func_8016CB80 */

typedef struct S_8016CB80_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_8016CB80_4;   /* temp_a0_2 in func_8016CB80 */

void func_8016CB80(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *base1 = arg1;
    register void *base2 ASM_REG("$17") = arg2;   /* MATCH pin: load-bearing for the whole function shape */
    void *base3 = arg3;
    M2C_UNK sp18;
    s32 temp_a0;
    s32 temp_v1_2;
    s32 scaled;
    s32 delta;
    s32 temp_v1_3;
    u16 temp_v0;
    u16 temp_v1_4;
    s32 temp_v1;
    u8 *temp_a0_2;
    register void *temp_v1_dispatch ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register u32 temp_v0_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *temp_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */

#define arg1 base1
#define arg2 base2
#define arg3 base3

    temp_v1 = ((S_8016CB80_0 *)arg0)->unk_9B;
    if (temp_v1 == 1) {
        goto block_10;
    }
    if ((s32) temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto block_0;
        }
        func_8016CDC0();
        return;
    }
    if (temp_v1 == 2) {
        goto block_14;
    }
    if (temp_v1 == 3) {
        goto block_18;
    }
    func_8016CDC0();
    return;
block_0:
    ((S_8016CB80_0 *)arg0)->unk_98 = (u16) (((S_8016CB80_0 *)arg0)->unk_98 | 8);
    ((S_8016CB80_1 *)arg3)->unk_1C = (s32) (((S_8016CB80_1 *)arg3)->unk_1C & 0xF7FFFFFF);
    ((S_8016CB80_0 *)arg0)->unk_9E = 5;
    ((S_8016CB80_0 *)arg0)->unk_A0 = 0;
    ((S_8016CB80_0 *)arg0)->unk_9B = (u8) (((S_8016CB80_0 *)arg0)->unk_9B + 1);
block_10:
    temp_a0 = ((S_8016CB80_0 *)arg0)->unk_9E;
    ((S_8016CB80_0 *)arg0)->unk_90 = (s32) (((S_8016CB80_0 *)arg0)->unk_90 - ((S_8016CB80_0 *)arg0)->unk_A0);
    if (temp_a0 != 0) {
        scaled = ((S_8016CB80_2 *)arg2)->unk_24;
        ASM_KEEP(scaled);   /* MATCH pin: retail schedule: same instructions, different order without it */
        delta = ((S_8016CB80_3 *)arg1)->unk_02 - 0x20;
        ((S_8016CB80_3 *)arg1)->unk_0C = (s32) ((s32) (((scaled << 6) - delta) << 0x10) / temp_a0);
        delta = ((S_8016CB80_3 *)arg1)->unk_06 - 0x20;
        ((S_8016CB80_3 *)arg1)->unk_10 = (s32) ((s32) (((((S_8016CB80_2 *)arg2)->unk_25 << 6) - delta) << 0x10) / (s16) ((S_8016CB80_0 *)arg0)->unk_9E);
        ((S_8016CB80_0 *)arg0)->unk_A0 = (s32) ((0 - func_800644B8(((S_8016CB80_0 *)arg0)->unk_9E * 0x199)) << 0xA);
    }
    ((S_8016CB80_0 *)arg0)->unk_90 = (s32) (((S_8016CB80_0 *)arg0)->unk_90 + ((S_8016CB80_0 *)arg0)->unk_A0);
    temp_v1_2 = (u16) ((S_8016CB80_0 *)arg0)->unk_9E - 1;
    ((S_8016CB80_0 *)arg0)->unk_9E = temp_v1_2;
    if ((temp_v1_2 << 0x10) < 0) {
        ((S_8016CB80_0 *)arg0)->unk_90 = 0;
        ((S_8016CB80_0 *)arg0)->unk_98 = (u16) (((S_8016CB80_0 *)arg0)->unk_98 & 0xFFF7);
        ((S_8016CB80_1 *)arg3)->unk_1C = (s32) (((S_8016CB80_1 *)arg3)->unk_1C | 0x08000000);
        ((S_8016CB80_0 *)arg0)->unk_9B = (u8) (((S_8016CB80_0 *)arg0)->unk_9B + 1);
    }
block_14:
    if (((S_8016CB80_1 *)arg3)->unk_1C & 0x08000000) {
        ((S_8016CB80_0 *)arg0)->unk_98 = (u16) (((S_8016CB80_0 *)arg0)->unk_98 & 0xFFF7);
        ((S_8016CB80_3 *)arg1)->unk_14 = 0;
        ((S_8016CB80_3 *)arg1)->unk_10 = 0;
        ((S_8016CB80_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_8016CB80_2 *)arg2)->unk_24, ((S_8016CB80_2 *)arg2)->unk_25);
        ((S_8016CB80_0 *)arg0)->unk_9B = (u8) (((S_8016CB80_0 *)arg0)->unk_9B + 1);
        func_8016CDC0();
        return;
    }
    goto block_22;
block_18:
    if (((S_8016CB80_0 *)arg0)->unk_B3 == 0) {
        temp_v1_dispatch = ((S_8016CB80_2 *)arg2)->unk_2C.p;
        ASM_KEEP(temp_v1_dispatch);   /* MATCH pin: retail basic-block layout depends on it */
        temp_v0_page = 0x80170000;
        ASM_KEEP(temp_v0_page);   /* MATCH pin: load-bearing for the whole function shape */
        temp_a1 = (u8 *)temp_v0_page + 0x467C;
        ASM_TAILSLOT_PIN(temp_a1);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8016CD88();
        return;
    }
    if (((S_8016CB80_2 *)arg2)->unk_2C.p2 != D_80174684) {
        (*(u8 **)((u8 *)arg2 + 0x2C)) = D_80174684;
        func_80047784(arg2, D_80174684[((s32) (D_80083228 + ((S_8016CB80_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    }
block_22:
    temp_v0 = ((S_8016CB80_0 *)arg0)->unk_96 - 1;
    ((S_8016CB80_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_8016CB80_3 *)arg1)->unk_14 = 0;
        ((S_8016CB80_3 *)arg1)->unk_10 = 0;
        ((S_8016CB80_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_8016CB80_2 *)arg2)->unk_24, ((S_8016CB80_2 *)arg2)->unk_25);
        func_800A4ACC(arg3);
        temp_a0_2 = D_80083460;
        if (((S_8016CB80_4 *)temp_a0_2)->unk_08 != 0) {
            ((S_8016CB80_4 *)temp_a0_2)->unk_08 = (s16) ((u16) ((S_8016CB80_4 *)temp_a0_2)->unk_08 - 1);
        }
        temp_v1_3 = ((S_8016CB80_1 *)arg3)->unk_1C;
        if (temp_v1_3 & 0x2000) {
            temp_v1_4 = ((S_8016CB80_1 *)arg3)->unk_46;
            if (!(temp_v1_4 & 0x8000)) {
                goto block_32;
            }
            ((S_8016CB80_1 *)arg3)->unk_46 = temp_v1_4 & 0x7FFF;
            func_8016CE8C(temp_a0_2);
            return;
        }
        if (temp_v1_3 & 0x410) {
            goto block_32;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_32;
        }
        ((S_8016CB80_1 *)arg3)->unk_2A = func_800A0818(((S_8016CB80_2 *)arg2)->unk_24, ((S_8016CB80_2 *)arg2)->unk_25, D_80082E80[0x24], D_80082E80[0x25], &sp18);
block_32:
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            ((S_8016CB80_0 *)arg0)->unk_8C = D_8016B778;
            func_800A9A04(arg3);
        }
    }
}

#undef arg1
#undef arg2
#undef arg3

/* MECHANISM: The 0x38 frame holds arg0/arg1/arg2/arg3 in s0/s2/s1/s3, with the s3 copy in the first branch slot.
   Promoted temporaries and statement boundaries reproduce the signed loads, interpolation order, and countdown CFG.
   Restoring the state increment closed the three-word cascade; v1/page carriers plus the tail-slot pin close the dispatcher j. */

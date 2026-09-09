#include "common.h"


typedef void (*Callback)(s32, void *, void *, void *);

typedef struct {
    u8 pad[0x3160];
    u8 *table[3];
} GlobalPage;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);

extern u8 *D_80083160[3];
extern GlobalPage D_80080000;
__asm__(".set D_80080000, 0x80080000");


typedef struct S_800D07C8_0 {
    u8 pad_00[0x8];
    union { s32 s32; u16 u16; } unk_08;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_0C;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_10;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    union { void * p; u8 * p2; } unk_20;   /* accessed as both */
    u16 unk_24;
    u8 pad_26[0xA];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x34];
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    u8 pad_8E[0x32];
    s32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
    u8 pad_106[0x2];
    u16 unk_108;
    u16 unk_10A;
} S_800D07C8_0;   /* scratch in func_800D07C8 */

typedef struct S_800D07C8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D07C8_1;   /* arg1 in func_800D07C8 */

typedef struct S_800D07C8_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800D07C8_2;   /* global_page->table[0] in func_800D07C8 */

typedef struct S_800D07C8_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_800D07C8_3;   /* arg2 in func_800D07C8 */

typedef struct S_800D07C8_4 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_800D07C8_4;   /* temp_s3 in func_800D07C8 */

typedef struct S_800D07C8_5_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800D07C8_5_pre;   /* the 0x4 bytes before temp_s0 in func_800D07C8, addressed as temp_s0[-1] */

typedef struct S_800D07C8_5 {
    u8 unk_00;
    u8 pad_01[0x10];
    u8 unk_11;
    u8 pad_12[0xC];
    u8 unk_1E;
    u8 pad_1F[0xA];
    u8 unk_29;
    u8 unk_2A;
} S_800D07C8_5;   /* temp_s0 in func_800D07C8 */

typedef struct S_800D07C8_6 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800D07C8_6;   /* table[0] in func_800D07C8 */

void func_800D07C8(s32 arg0, u8 *arg1, u8 *arg2, s16 arg3) {
    u8 matrix[32];
    register u8 *scratch ASM_REG("$17") = (u8 *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *temp_s0;
    u8 *temp_s2;
    u8 *temp_s3;
    register u8 *temp_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    s32 var_v1_2;
    u32 temp_v0_7;
    u16 temp_v1_3;
    register u8 temp_a0_2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 var_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register GlobalPage *global_page ASM_REG("$4") = &D_80080000;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    Callback callback;

    ((S_800D07C8_0 *)scratch)->unk_20.p = global_page->table[0] + 0xB0;
    ((S_800D07C8_0 *)scratch)->unk_E4 = ((S_800D07C8_1 *)arg1)->unk_02;
    ((S_800D07C8_0 *)scratch)->unk_E8 = ((S_800D07C8_1 *)arg1)->unk_06;
    ((S_800D07C8_0 *)scratch)->unk_EC = ((S_800D07C8_1 *)arg1)->unk_0A;
    ((S_800D07C8_0 *)scratch)->unk_8C = 0;
    ((S_800D07C8_0 *)scratch)->unk_84 = 0;
    ((S_800D07C8_0 *)scratch)->unk_7C = 0;
    ((S_800D07C8_0 *)scratch)->unk_74 = 0;
    temp_s4 = ((S_800D07C8_2 *)(global_page->table[0]))->unk_8D0;
    ((S_800D07C8_3 *)arg2)->unk_14 |= 0x8000;
    func_800649A0();
    ((S_800D07C8_0 *)scratch)->unk_108 = ((S_800D07C8_3 *)arg2)->unk_20;
    ((S_800D07C8_0 *)scratch)->unk_10A = ((S_800D07C8_3 *)arg2)->unk_22;
    ((S_800D07C8_0 *)scratch)->unk_30 = ((S_800D07C8_3 *)arg2)->unk_1C * 2;
    ((S_800D07C8_0 *)scratch)->unk_34 = ((S_800D07C8_3 *)arg2)->unk_1E * 2;
    ((S_800D07C8_0 *)scratch)->unk_38 = 0;
    ((S_800D07C8_0 *)scratch)->unk_100 = ((S_800D07C8_3 *)arg2)->unk_16;
    ((S_800D07C8_0 *)scratch)->unk_104 = ((S_800D07C8_3 *)arg2)->unk_1A;
    ((S_800D07C8_0 *)scratch)->unk_102 = ((S_800D07C8_3 *)arg2)->unk_18;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    temp_s0 = temp_s4 + 7;
    func_80064AE0(matrix);
    func_80064840(matrix, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    temp_s3 = ((S_800D07C8_3 *)arg2)->unk_08;
    temp_s2 = temp_s3 + 8;
    ((S_800D07C8_0 *)scratch)->unk_24 = ((S_800D07C8_3 *)arg2)->unk_14;
    for (;;) {
        ASM_KEEP_NV(temp_s2);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        if (!(((S_800D07C8_4 *)temp_s3)->unk_00.u & 0x20)) {
            ((S_800D07C8_0 *)scratch)->unk_08.s32 = (*(u8 *)((u8 *)temp_s2 + 0));
            ((S_800D07C8_0 *)scratch)->unk_0C.s32 = (*(u8 *)((u8 *)temp_s2 + 1));
            ((S_800D07C8_0 *)scratch)->unk_10.s32 = (*(u8 *)((u8 *)temp_s2 + 2));
            ((S_800D07C8_0 *)scratch)->unk_14.s32 = (*(u8 *)((u8 *)temp_s2 + 3));
            if ((((S_800D07C8_4 *)temp_s3)->unk_00.u ^ ((S_800D07C8_0 *)scratch)->unk_24) & 1) {
                temp_v0_3 = (0 - (s8)(*(volatile u8 *)((u8 *)temp_s2 + -6))) - ((S_800D07C8_0 *)scratch)->unk_108;
                ((S_800D07C8_0 *)scratch)->unk_80 = temp_v0_3;
                ((S_800D07C8_0 *)scratch)->unk_70 = temp_v0_3;
                temp_v0_3 -= ((S_800D07C8_0 *)scratch)->unk_10.u16;
            } else {
                temp_v0_3 = (s8)(*(volatile u8 *)((u8 *)temp_s2 + -6)) - ((S_800D07C8_0 *)scratch)->unk_108;
                ((S_800D07C8_0 *)scratch)->unk_80 = temp_v0_3;
                ((S_800D07C8_0 *)scratch)->unk_70 = temp_v0_3;
                temp_v0_3 = temp_v0_3 + ((S_800D07C8_0 *)scratch)->unk_10.u16;
            }
            ((S_800D07C8_0 *)scratch)->unk_88 = temp_v0_3;
            ((S_800D07C8_0 *)scratch)->unk_78 = temp_v0_3;
            if ((((S_800D07C8_4 *)temp_s3)->unk_00.u ^ ((S_800D07C8_0 *)scratch)->unk_24) & 2) {
                temp_v0_6 = (0 - (s8)(*(volatile u8 *)((u8 *)temp_s2 + -5))) - ((S_800D07C8_0 *)scratch)->unk_10A;
                ((S_800D07C8_0 *)scratch)->unk_7A = temp_v0_6;
                ((S_800D07C8_0 *)scratch)->unk_72 = temp_v0_6;
                temp_v0_6 -= ((S_800D07C8_0 *)scratch)->unk_14.u16;
            } else {
                temp_v0_6 = (s8)(*(volatile u8 *)((u8 *)temp_s2 + -5)) - ((S_800D07C8_0 *)scratch)->unk_10A;
                ((S_800D07C8_0 *)scratch)->unk_7A = temp_v0_6;
                ((S_800D07C8_0 *)scratch)->unk_72 = temp_v0_6;
                temp_v0_6 = temp_v0_6 + ((S_800D07C8_0 *)scratch)->unk_14.u16;
            }
            ((S_800D07C8_0 *)scratch)->unk_8A = temp_v0_6;
            ((S_800D07C8_0 *)scratch)->unk_82 = temp_v0_6;

            ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            temp_v0_7 = (func_80065590(scratch + 0x70, scratch + 0x78,
                                       scratch + 0x80, scratch + 0x88,
                                       temp_s4 + 8, temp_s4 + 0x14,
                                       temp_s4 + 0x20, temp_s4 + 0x2C,
                                       scratch + 0x90, scratch + 0x94) - arg3) - 6;
            ((S_800D07C8_0 *)scratch)->unk_C0 = temp_v0_7;
            if (temp_v0_7 < 0x1E0U) {
                var_a1 = 0;
                if ((u32)(((*(u16 *)((u8 *)temp_s0 + 1)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 masked;
                    masked = (u32)(((*(u16 *)((u8 *)temp_s0 + 3)) + 0x20) & 0xFFFF);
                    var_a1 = masked < 0x121U;
                }
                var_v1 = 0;
                if ((u32)(((*(u16 *)((u8 *)temp_s0 + 0xD)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 masked;
                    masked = (u32)(((*(u16 *)((u8 *)temp_s0 + 0xF)) + 0x20) & 0xFFFF);
                    var_v1 = masked < 0x121U;
                }
                var_a0 = 0;
                temp_a1 = var_a1 | var_v1;
                if ((u32)(((*(u16 *)((u8 *)temp_s0 + 0x19)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 masked;
                    masked = (u32)(((*(u16 *)((u8 *)temp_s0 + 0x1B)) + 0x20) & 0xFFFF);
                    var_a0 = masked < 0x121U;
                }
                var_v1_2 = 0;
                temp_a0 = temp_a1 | var_a0;
                if ((u32)(((*(u16 *)((u8 *)temp_s0 + 0x25)) + 0x20) & 0xFFFF) < 0x181U) {
                    u32 masked;
                    masked = (u32)(((*(u16 *)((u8 *)temp_s0 + 0x27)) + 0x20) & 0xFFFF);
                    var_v1_2 = masked < 0x121U;
                }
                if ((temp_a0 | var_v1_2) != 0) {
                    ((S_800D07C8_3 *)arg2)->unk_14 &= 0x7FFF;
                    temp_v1 = ((S_800D07C8_0 *)scratch)->unk_10.s32 + ((S_800D07C8_0 *)scratch)->unk_08.s32;
                    ((S_800D07C8_0 *)scratch)->unk_10.s32 = temp_v1;
                    if (temp_v1 & 0x100) {
                        ((S_800D07C8_0 *)scratch)->unk_10.s32 = temp_v1 - 1;
                    }
                    temp_v1_2 = ((S_800D07C8_0 *)scratch)->unk_14.s32 + ((S_800D07C8_0 *)scratch)->unk_0C.s32;
                    ((S_800D07C8_0 *)scratch)->unk_14.s32 = temp_v1_2;
                    if (temp_v1_2 & 0x100) {
                        ((S_800D07C8_0 *)scratch)->unk_14.s32 = temp_v1_2 - 1;
                    }
                    ((S_800D07C8_0 *)scratch)->unk_0C.s32 <<= 8;
                    ((S_800D07C8_0 *)scratch)->unk_14.s32 <<= 8;
                    if (((S_800D07C8_0 *)scratch)->unk_24 & 0x100) {
                        (*(s16 *)((u8 *)temp_s0 + 7)) = ((S_800D07C8_3 *)arg2)->unk_12;
                    } else {
                        (*(s16 *)((u8 *)temp_s0 + 7)) = ((S_800D07C8_3 *)arg2)->unk_12 + (*(u16 *)((u8 *)temp_s2 + -2));
                    }
                    (*(s16 *)((u8 *)temp_s0 + 5)) = ((S_800D07C8_0 *)scratch)->unk_0C.u16 + ((S_800D07C8_0 *)scratch)->unk_08.u16;
                    (*(s16 *)((u8 *)temp_s0 + 0x11)) = ((S_800D07C8_0 *)scratch)->unk_0C.u16 + ((S_800D07C8_0 *)scratch)->unk_10.u16;
                    {
                        s32 continuation_base = ((S_800D07C8_3 *)arg2)->unk_10;
                        s32 continuation_v0;
                        if (continuation_base != 0) {
                            continuation_v0 = continuation_base + ((*(u16 *)((u8 *)temp_s2 + -4)) & 0xFF9F);
                        } else {
                            continuation_v0 = (*(u16 *)((u8 *)temp_s2 + -4));
                        }
                        (*(u16 *)((u8 *)temp_s0 + 0x13)) = continuation_v0;
                    }
                    (*(s16 *)((u8 *)temp_s0 + 0x1D)) = ((S_800D07C8_0 *)scratch)->unk_14.u16 + ((S_800D07C8_0 *)scratch)->unk_08.u16;
                    (*(s16 *)((u8 *)temp_s0 + 0x29)) = ((S_800D07C8_0 *)scratch)->unk_14.u16 + ((S_800D07C8_0 *)scratch)->unk_10.u16;
                    if ((*(s16 *)((u8 *)temp_s0 + 1)) > (*(s16 *)((u8 *)temp_s0 + 0x25))) {
                        ((S_800D07C8_5 *)temp_s0)->unk_11--;
                        ((S_800D07C8_5 *)temp_s0)->unk_29--;
                    }
                    if ((*(s16 *)((u8 *)temp_s0 + 3)) > (*(s16 *)((u8 *)temp_s0 + 0x27))) {
                        ((S_800D07C8_5 *)temp_s0)->unk_1E--;
                        ((S_800D07C8_5 *)temp_s0)->unk_2A--;
                    }
                    temp_v0_8 = ((S_800D07C8_3 *)arg2)->unk_0C;
                    (*(s32 *)((u8 *)temp_s0 + 0x21)) = 0;
                    (*(s32 *)((u8 *)temp_s0 + 0x15)) = 0;
                    ((S_800D07C8_5_pre *)temp_s0)[-1].unk_00 = 0xC;
                    (*(s32 *)((u8 *)temp_s0 + 9)) = temp_v0_8;
                    (*(s32 *)((u8 *)temp_s0 + -3)) = temp_v0_8;
                    temp_a0_2 = (*(u8 *)((u8 *)temp_s2 + -7));
                    ((S_800D07C8_5 *)temp_s0)->unk_00 = temp_a0_2;
                    temp_v1_3 = ((S_800D07C8_0 *)scratch)->unk_24;
                    if (temp_v1_3 & 8) {
                        var_v0 = temp_v1_3 & 4;
                        if (var_v0 == 0) {
                            var_v0 = temp_a0_2 & 0xFD;
                        } else {
                            var_v0 = temp_a0_2 | 2;
                        }
                        ((S_800D07C8_5 *)temp_s0)->unk_00 = var_v0;
                    }
                    {
                        register u8 *call_s4 ASM_REG("$5") = temp_s4;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        temp_s0 += 0x34;
                        temp_s4 += 0x34;
                        func_8006658C(((S_800D07C8_0 *)scratch)->unk_20.p2 + (((S_800D07C8_0 *)scratch)->unk_C0 * 4), call_s4);
                    }
                    ASM_KEEP(temp_s0);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                    ASM_KEEP(temp_s4);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                }
            }
        } else {
            callback = (*(Callback *)((u8 *)temp_s2 + 0));
            if (callback != 0) {
                callback(arg0, arg1, arg2, temp_s3);
            }
        }

        temp_s2 += 0xC;
        if (((S_800D07C8_4 *)temp_s3)->unk_00.s >= 0) {
            temp_s3 += 0xC;
        } else {
            break;
        }
    }
    ASM_KEEP(temp_s2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    func_80064A40();
    {
        register u8 **table ASM_REG("$8") = D_80083160;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((S_800D07C8_6 *)(table[0]))->unk_8D0 = temp_s4;
    }
}

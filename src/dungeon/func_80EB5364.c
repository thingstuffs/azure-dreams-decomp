#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80047738();
M2C_UNK func_800478B8();
M2C_UNK func_800A020C();
s32 func_800A9E70();
M2C_UNK func_800AA36C();
s32 func_800BCB04();
void func_80170CF8() __attribute__((noreturn));
void func_80170DA0() __attribute__((noreturn));
void func_80170E0C() __attribute__((noreturn));
void func_80170EB8() __attribute__((noreturn));
void func_80170EC0() __attribute__((noreturn));
void func_80171064() __attribute__((noreturn));
void func_8017106C() __attribute__((noreturn));
void func_801710D8() __attribute__((noreturn));
extern u8 D_8006CCF8[];
extern s16 D_80083228[];
extern u16 D_80083462[];
extern M2C_UNK D_801711A4[];
extern M2C_UNK D_80174174[];
extern M2C_UNK D_8017418C[];
extern M2C_UNK D_801741D4[];


typedef struct S_80170B64_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4D];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x1A];
    M2C_UNK (*unk_8C)(void *, void *, void *, void *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x2];
    union { s8 s; u8 u; } unk_9D;   /* accessed as both */
    u8 pad_9E[0x2];
    union { u16 u; s16 s; } unk_A0;   /* accessed as both */
    u8 pad_A2[0x6];
    s16 unk_A8;
    u8 pad_AA[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_AC;   /* overlapping accesses */
} S_80170B64_0;   /* arg0 in func_80170B64 */

typedef struct S_80170B64_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170B64_1;   /* arg1 in func_80170B64 */

typedef struct S_80170B64_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { void * p; s32 i; } unk_2C;   /* accessed as both */
} S_80170B64_2;   /* arg2 in func_80170B64 */

typedef struct S_80170B64_3 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170B64_3;   /* work in func_80170B64 */

void func_80170B64(void *in0, void *in1, void *in2)
{
    register void *p0 ASM_REG("$17") = in0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *p1 ASM_REG("$21") = in1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *p2 ASM_REG("$20") = in2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *work ASM_REG("$18") = p0;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    M2C_UNK (*temp_v0)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1)(void *, void *, void *, void *);
    u8 *var_v0;
    s32 temp_a0_2;
    s32 cmp_a1;
    s16 temp_a0_3;
    s16 temp_a0_4;
    u16 held_92;
    s16 temp_s3;
    s16 temp_v0_3;
    s32 var_a1;
    s32 temp_v0_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s16 temp_s0;
    u16 temp_v1_2;
#ifdef __mips__
    u32 tail_page;
    u32 tail_flag;
#endif

#define arg0 p0
#define arg1 p1
#define arg2 p2

    if (D_80083462[0] & 0x2000) {
        void *raw0 = in0;
        temp_v1 = ((S_80170B64_0 *)arg0)->unk_8C;
        if (temp_v1 == &D_801711A4) {
            ASM_KEEP(raw0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            temp_v1(raw0, arg1, arg2, raw0);
            return;
        }
        ((S_80170B64_0 *)arg0)->unk_71 &= 0x7F;
        return;
    }

    ASM_KEEP(p0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    temp_s0 = (s8)((S_80170B64_0 *)arg0)->unk_6D;
    if (func_800A9E70(arg0, arg1, arg2, arg0) == 0) {
        temp_v0 = ((S_80170B64_0 *)arg0)->unk_8C;
        if (temp_v0 != 0) {
            temp_v0(arg0, arg1, arg2, arg0);
        }
        ((M2C_UNK (**)(void *, void *, void *, void *))&D_801741D4)
            [((S_80170B64_0 *)arg0)->unk_9A](arg0, arg1, arg2, arg0);
        if ((s16)temp_s0 != (s8)((S_80170B64_0 *)arg0)->unk_6D) {
            func_800AA36C(arg0, arg1, arg2, arg0);
        }
        ((S_80170B64_1 *)arg1)->unk_00.at00.v += ((S_80170B64_1 *)arg1)->unk_0C;
        ((S_80170B64_1 *)arg1)->unk_04.at00.v += ((S_80170B64_1 *)arg1)->unk_10;
        if (!(((S_80170B64_0 *)arg0)->unk_1C & 0x40000) &&
            !(((S_80170B64_0 *)arg0)->unk_98 & 8)) {
            ((S_80170B64_1 *)arg1)->unk_14 = ((S_80170B64_1 *)arg1)->unk_14 +
                (((S_80170B64_0 *)arg0)->unk_9D.s * 0x14000);
            ((S_80170B64_0 *)arg0)->unk_9D.u++;
            func_80170CF8();
            return;
        }
        ((S_80170B64_0 *)arg0)->unk_9D.s = 0;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_80170B64_0 *)arg0)->unk_90.at00.v = ((S_80170B64_0 *)arg0)->unk_90.at00.v +
            ((S_80170B64_1 *)arg1)->unk_14;
        temp_v1_2 = ((S_80170B64_2 *)arg2)->unk_14;
        if (!(temp_v1_2 & 0x8000)) {
            temp_s3 = ((D_80083228[0] + ((S_80170B64_3 *)work)->unk_2A + 0x100) >> 9) & 7;
            if (((S_80170B64_0 *)arg0)->unk_94 != temp_s3) {
                func_80047738(arg2,
                    *(((u8 *)((S_80170B64_2 *)arg2)->unk_2C.p) + temp_s3),
                    ((S_80170B64_2 *)arg2)->unk_04.s8);
                ((S_80170B64_0 *)arg0)->unk_94 = temp_s3;
            }
            if (D_8006CCF8[temp_s3] != 0) {
#ifdef __mips__
                tail_flag = ((S_80170B64_2 *)arg2)->unk_14 | 1;
                ASM_TAILSLOT_PIN(tail_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif
                func_80170DA0();
                return;
            }
            ((S_80170B64_2 *)arg2)->unk_14 &= 0xFFFE;
            func_800A020C(((S_80170B64_3 *)work)->unk_1C.s, arg2 + 0xC);
            if (!(((S_80170B64_3 *)work)->unk_1C.s & 0x20)) {
                if (!(((S_80170B64_2 *)arg2)->unk_14 & 0x40)) {
                    func_800478B8(arg2);
#ifdef __mips__
                    tail_page = 0xF7FF0000;
                    ASM_PAGEBASE_PIN(tail_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
#endif
                    func_80170E0C();
                    return;
                }
                goto block_26;
            }
            ((S_80170B64_2 *)arg2)->unk_14 |= 0x7000;
            ((S_80170B64_3 *)work)->unk_1C.s &= 0xFFFBFFFF;
block_26:
            temp_v1_3 = ((S_80170B64_3 *)work)->unk_1C.s & 0xF7FFFFFF;
            ((S_80170B64_3 *)work)->unk_1C.s = temp_v1_3;
            if (temp_v1_3 & 0x40000) {
                if (!(((S_80170B64_2 *)arg2)->unk_14 & 0x40)) {
                    temp_v1_4 = ((S_80170B64_2 *)arg2)->unk_2C.i;
                    if (temp_v1_4 == (s32)&D_8017418C) {
                        ((S_80170B64_0 *)arg0)->unk_AC.at00.v = 0;
                        func_80170EC0();
                        return;
                    }
                    if (temp_v1_4 == (s32)&D_80174174) {
                        ((S_80170B64_0 *)arg0)->unk_A0.u++;
                        if (((S_80170B64_2 *)arg2)->unk_04.u16 == 0x100) {
                            ((S_80170B64_0 *)arg0)->unk_A0.u = 0;
                            ((S_80170B64_0 *)arg0)->unk_AC.at00.v = 0;
                        }
                        if (((S_80170B64_0 *)arg0)->unk_A0.s < 5) {
                            ((S_80170B64_0 *)arg0)->unk_AC.at00.v += -0x33333;
                        } else {
                            ((S_80170B64_0 *)arg0)->unk_AC.at00.v += 0x12492;
                        }
                        goto block_38;
                    }
                    goto block_38;
                }
block_38:
                if (!(((S_80170B64_0 *)arg0)->unk_98 & 8)) {
                    var_a1 = func_800BCB04(((S_80170B64_1 *)arg1)->unk_00.at02.v,
                        ((S_80170B64_1 *)arg1)->unk_04.at02.v,
                        (s16)(((S_80170B64_3 *)work)->unk_88 - 0x20)) -
                        ((S_80170B64_3 *)work)->unk_88;
                    if (((S_80170B64_0 *)arg0)->unk_90.at02.v > ((s16)var_a1 - 0x20)) {
                        ((S_80170B64_0 *)arg0)->unk_90.at02.v =
                            ((S_80170B64_0 *)arg0)->unk_90.at02u.v - 8;
                    } else if (((S_80170B64_0 *)arg0)->unk_90.at02.v <
                               ((s16)var_a1 - 0x28)) {
                        ((S_80170B64_0 *)arg0)->unk_90.at02.v =
                            ((S_80170B64_0 *)arg0)->unk_90.at02u.v + 8;
                    }
                }
                goto block_64;
            }
            goto block_45;
        }
        if (temp_v1_2 & 0x800) {
            ((S_80170B64_2 *)arg2)->unk_14 = temp_v1_2 & 0x8FFF;
        } else {
            ((S_80170B64_2 *)arg2)->unk_14 = temp_v1_2 | 0x7000;
        }
        temp_v1_5 = ((S_80170B64_3 *)work)->unk_1C.s & 0xF7FFFFFF;
        ((S_80170B64_3 *)work)->unk_1C.s = temp_v1_5;
        if (!(temp_v1_5 & 0x40000)) {
block_45:
            temp_v0_2 = ((S_80170B64_0 *)arg0)->unk_AC.at00.v;
            ((S_80170B64_0 *)arg0)->unk_A8 = 0;
            ((S_80170B64_0 *)arg0)->unk_AC.at00.v = 0;
            ((S_80170B64_0 *)arg0)->unk_90.at00.v -= temp_v0_2;
            if (!(((S_80170B64_0 *)arg0)->unk_98 & 8)) {
                temp_a0_4 = func_800BCB04(((S_80170B64_1 *)arg1)->unk_00.at02.v,
                    ((S_80170B64_1 *)arg1)->unk_04.at02.v,
                    (s16)(((S_80170B64_3 *)work)->unk_88 - 0x20)) -
                    ((S_80170B64_3 *)work)->unk_88;
                if (temp_a0_4 < ((S_80170B64_0 *)arg0)->unk_90.at02.v) {
                    ((S_80170B64_0 *)arg0)->unk_90.at02.v = temp_a0_4;
                    ((S_80170B64_0 *)arg0)->unk_9D.s = 0;
                    ((S_80170B64_1 *)arg1)->unk_14 = 0;
                    ((S_80170B64_3 *)work)->unk_1C.u |= 0x08000000;
                    func_801710D8();
                    return;
                }
            }
            goto block_64;
        }
        if (!(((S_80170B64_2 *)arg2)->unk_14 & 0x40)) {
            temp_v1_6 = ((S_80170B64_2 *)arg2)->unk_2C.i;
            if (temp_v1_6 == (s32)&D_8017418C) {
                ((S_80170B64_0 *)arg0)->unk_AC.at00.v = 0;
                func_8017106C();
                return;
            }
            if (temp_v1_6 == (s32)&D_80174174) {
                ((S_80170B64_0 *)arg0)->unk_A0.u++;
                if (((S_80170B64_2 *)arg2)->unk_04.u16 == 0x100) {
                    ((S_80170B64_0 *)arg0)->unk_A0.u = 0;
                    ((S_80170B64_0 *)arg0)->unk_AC.at00.v = 0;
                }
                if (((S_80170B64_0 *)arg0)->unk_A0.s < 5) {
                    ((S_80170B64_0 *)arg0)->unk_AC.at00.v += -0x33333;
                } else {
                    ((S_80170B64_0 *)arg0)->unk_AC.at00.v += 0x12492;
                }
                goto block_60;
            }
            goto block_60;
        }
block_60:
        if (!(((S_80170B64_0 *)arg0)->unk_98 & 8)) {
            var_a1 = func_800BCB04(((S_80170B64_1 *)arg1)->unk_00.at02.v,
                ((S_80170B64_1 *)arg1)->unk_04.at02.v,
                (s16)(((S_80170B64_3 *)work)->unk_88 - 0x20)) -
            ((S_80170B64_3 *)work)->unk_88;
            if (((S_80170B64_0 *)arg0)->unk_90.at02.v > ((s16)var_a1 - 0x20)) {
                ((S_80170B64_0 *)arg0)->unk_90.at02.v =
                    ((S_80170B64_0 *)arg0)->unk_90.at02u.v - 8;
            } else if (((S_80170B64_0 *)arg0)->unk_90.at02.v < ((s16)var_a1 - 0x28)) {
                ((S_80170B64_0 *)arg0)->unk_90.at02.v =
                    ((S_80170B64_0 *)arg0)->unk_90.at02u.v + 8;
            }
        }
block_64:
        temp_v1_7 = ((S_80170B64_3 *)work)->unk_1C.s;
        if (temp_v1_7 & 0x40000000) {
            ((S_80170B64_3 *)work)->unk_1C.s = temp_v1_7 & 0xBFFFFFFF;
            temp_v0_3 = func_800BCB04(
                (((S_80170B64_2 *)arg2)->unk_24 << 6) | 0x20,
                (((S_80170B64_2 *)arg2)->unk_25 << 6) | 0x20,
                (s16)(((S_80170B64_3 *)work)->unk_88 - 0x20));
            if (temp_v0_3 < 0x200) {
                ((S_80170B64_0 *)arg0)->unk_90.at02.v = (u16)((S_80170B64_0 *)arg0)->unk_90.at02.v +
                    (((S_80170B64_3 *)work)->unk_88 - temp_v0_3);
                ((S_80170B64_3 *)work)->unk_88 = temp_v0_3;
            }
        }
        ((S_80170B64_1 *)arg1)->unk_0A = ((S_80170B64_0 *)arg0)->unk_AC.at02.v +
            (((S_80170B64_3 *)work)->unk_88 + (u16)((S_80170B64_0 *)arg0)->unk_90.at02.v);
        ((S_80170B64_2 *)arg2)->unk_14 |= 0x40;
    }

#undef arg0
#undef arg1
#undef arg2
}

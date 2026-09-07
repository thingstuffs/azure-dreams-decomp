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
void func_8017117C() __attribute__((noreturn));
extern u8 D_8006CCF8[];
extern s16 D_80083228[];
extern u16 D_80083462[];
extern M2C_UNK D_801711A4[];
extern M2C_UNK D_80174174[];
extern M2C_UNK D_8017418C[];
extern M2C_UNK D_801741D4[];

void func_80170B64(void *in0, void *in1, void *in2)
{
    register void *p0 ASM_REG("$17") = in0;
    register void *p1 ASM_REG("$21") = in1;
    register void *p2 ASM_REG("$20") = in2;
    register void *work ASM_REG("$18") = p0;
    M2C_UNK (*temp_v0)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1)(void *, void *, void *, void *);
    u8 *var_v0;
    register s32 temp_a0_2 ASM_REG("$4");
    register s32 cmp_a1 ASM_REG("$2");
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
    register u32 tail_page ASM_REG("$2");
    register u32 tail_flag ASM_REG("$2");
#endif

#define arg0 p0
#define arg1 p1
#define arg2 p2

    if (D_80083462[0] & 0x2000) {
        register void *raw0 ASM_REG("$4") = in0;
        temp_v1 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v1 == &D_801711A4) {
            ASM_KEEP(raw0);
            temp_v1(raw0, arg1, arg2, raw0);
            func_8017117C();
            return;
        }
        M2C_FIELD(arg0, u8 *, 0x71) &= 0x7F;
        func_8017117C();
        return;
    }

    ASM_KEEP(p0);
    ASM_KEEP(p1);
    ASM_KEEP(p2);

    temp_s0 = (s8)M2C_FIELD(arg0, u8 *, 0x6D);
    if (func_800A9E70(arg0, arg1, arg2, arg0) == 0) {
        temp_v0 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v0 != 0) {
            temp_v0(arg0, arg1, arg2, arg0);
        }
        ((M2C_UNK (**)(void *, void *, void *, void *))&D_801741D4)
            [M2C_FIELD(arg0, u8 *, 0x9A)](arg0, arg1, arg2, arg0);
        if ((s16)temp_s0 != (s8)M2C_FIELD(arg0, u8 *, 0x6D)) {
            func_800AA36C(arg0, arg1, arg2, arg0);
        }
        M2C_FIELD(arg1, s32 *, 0) += M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(arg1, s32 *, 4) += M2C_FIELD(arg1, s32 *, 0x10);
        if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x40000) &&
            !(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
            M2C_FIELD(arg1, s32 *, 0x14) = M2C_FIELD(arg1, s32 *, 0x14) +
                (M2C_FIELD(arg0, s8 *, 0x9D) * 0x14000);
            M2C_FIELD(arg0, u8 *, 0x9D)++;
            func_80170CF8();
            return;
        }
        M2C_FIELD(arg0, s8 *, 0x9D) = 0;
        ASM_MEM_BARRIER();
        M2C_FIELD(arg0, s32 *, 0x90) = M2C_FIELD(arg0, s32 *, 0x90) +
            M2C_FIELD(arg1, s32 *, 0x14);
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (!(temp_v1_2 & 0x8000)) {
            temp_s3 = ((D_80083228[0] + M2C_FIELD(work, s16 *, 0x2A) + 0x100) >> 9) & 7;
            if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s3) {
                func_80047738(arg2,
                    *(((u8 *)M2C_FIELD(arg2, void **, 0x2C)) + temp_s3),
                    M2C_FIELD(arg2, s8 *, 4));
                M2C_FIELD(arg0, s16 *, 0x94) = temp_s3;
            }
            if (D_8006CCF8[temp_s3] != 0) {
#ifdef __mips__
                tail_flag = M2C_FIELD(arg2, u16 *, 0x14) | 1;
                ASM_TAILSLOT_PIN(tail_flag);
#endif
                func_80170DA0();
                return;
            }
            M2C_FIELD(arg2, u16 *, 0x14) &= 0xFFFE;
            func_800A020C(M2C_FIELD(work, s32 *, 0x1C), arg2 + 0xC);
            if (!(M2C_FIELD(work, s32 *, 0x1C) & 0x20)) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    func_800478B8(arg2);
#ifdef __mips__
                    tail_page = 0xF7FF0000;
                    ASM_PAGEBASE_PIN(tail_page);
#endif
                    func_80170E0C();
                    return;
                }
                goto block_26;
            }
            M2C_FIELD(arg2, u16 *, 0x14) |= 0x7000;
            M2C_FIELD(work, s32 *, 0x1C) &= 0xFFFBFFFF;
block_26:
            temp_v1_3 = M2C_FIELD(work, s32 *, 0x1C) & 0xF7FFFFFF;
            M2C_FIELD(work, s32 *, 0x1C) = temp_v1_3;
            if (temp_v1_3 & 0x40000) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    temp_v1_4 = M2C_FIELD(arg2, s32 *, 0x2C);
                    if (temp_v1_4 == (s32)&D_8017418C) {
                        M2C_FIELD(arg0, s32 *, 0xAC) = 0;
                        func_80170EC0();
                        return;
                    }
                    if (temp_v1_4 == (s32)&D_80174174) {
                        M2C_FIELD(arg0, u16 *, 0xA0)++;
                        if (M2C_FIELD(arg2, u16 *, 4) == 0x100) {
                            M2C_FIELD(arg0, u16 *, 0xA0) = 0;
                            M2C_FIELD(arg0, s32 *, 0xAC) = 0;
                        }
                        if (M2C_FIELD(arg0, s16 *, 0xA0) < 5) {
                            M2C_FIELD(arg0, s32 *, 0xAC) += -0x33333;
                        } else {
                            M2C_FIELD(arg0, s32 *, 0xAC) += 0x12492;
                        }
                        goto block_38;
                    }
                    goto block_38;
                }
block_38:
                if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
                    var_a1 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2),
                        M2C_FIELD(arg1, u16 *, 6),
                        (s16)(M2C_FIELD(work, u16 *, 0x88) - 0x20)) -
                        M2C_FIELD(work, u16 *, 0x88);
                    if (M2C_FIELD(arg0, s16 *, 0x92) > ((s16)var_a1 - 0x20)) {
                        M2C_FIELD(arg0, s16 *, 0x92) =
                            M2C_FIELD(arg0, u16 *, 0x92) - 8;
                    } else if (M2C_FIELD(arg0, s16 *, 0x92) <
                               ((s16)var_a1 - 0x28)) {
                        M2C_FIELD(arg0, s16 *, 0x92) =
                            M2C_FIELD(arg0, u16 *, 0x92) + 8;
                    }
                }
                goto block_64;
            }
            goto block_45;
        }
        if (temp_v1_2 & 0x800) {
            M2C_FIELD(arg2, u16 *, 0x14) = temp_v1_2 & 0x8FFF;
        } else {
            M2C_FIELD(arg2, u16 *, 0x14) = temp_v1_2 | 0x7000;
        }
        temp_v1_5 = M2C_FIELD(work, s32 *, 0x1C) & 0xF7FFFFFF;
        M2C_FIELD(work, s32 *, 0x1C) = temp_v1_5;
        if (!(temp_v1_5 & 0x40000)) {
block_45:
            temp_v0_2 = M2C_FIELD(arg0, s32 *, 0xAC);
            M2C_FIELD(arg0, s16 *, 0xA8) = 0;
            M2C_FIELD(arg0, s32 *, 0xAC) = 0;
            M2C_FIELD(arg0, s32 *, 0x90) -= temp_v0_2;
            if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
                temp_a0_4 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2),
                    M2C_FIELD(arg1, u16 *, 6),
                    (s16)(M2C_FIELD(work, u16 *, 0x88) - 0x20)) -
                    M2C_FIELD(work, u16 *, 0x88);
                ASM_SCHED_BARRIER();
                if (temp_a0_4 < M2C_FIELD(arg0, s16 *, 0x92)) {
                    M2C_FIELD(arg0, s16 *, 0x92) = temp_a0_4;
                    M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(work, u32 *, 0x1C) |= 0x08000000;
                    func_801710D8();
                    return;
                }
            }
            goto block_64;
        }
        if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
            temp_v1_6 = M2C_FIELD(arg2, s32 *, 0x2C);
            if (temp_v1_6 == (s32)&D_8017418C) {
                M2C_FIELD(arg0, s32 *, 0xAC) = 0;
                func_8017106C();
                return;
            }
            if (temp_v1_6 == (s32)&D_80174174) {
                M2C_FIELD(arg0, u16 *, 0xA0)++;
                if (M2C_FIELD(arg2, u16 *, 4) == 0x100) {
                    M2C_FIELD(arg0, u16 *, 0xA0) = 0;
                    M2C_FIELD(arg0, s32 *, 0xAC) = 0;
                }
                if (M2C_FIELD(arg0, s16 *, 0xA0) < 5) {
                    M2C_FIELD(arg0, s32 *, 0xAC) += -0x33333;
                } else {
                    M2C_FIELD(arg0, s32 *, 0xAC) += 0x12492;
                }
                goto block_60;
            }
            goto block_60;
        }
block_60:
        if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
            var_a1 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2),
                M2C_FIELD(arg1, u16 *, 6),
                (s16)(M2C_FIELD(work, u16 *, 0x88) - 0x20)) -
            M2C_FIELD(work, u16 *, 0x88);
            if (M2C_FIELD(arg0, s16 *, 0x92) > ((s16)var_a1 - 0x20)) {
                M2C_FIELD(arg0, s16 *, 0x92) =
                    M2C_FIELD(arg0, u16 *, 0x92) - 8;
            } else if (M2C_FIELD(arg0, s16 *, 0x92) < ((s16)var_a1 - 0x28)) {
                M2C_FIELD(arg0, s16 *, 0x92) =
                    M2C_FIELD(arg0, u16 *, 0x92) + 8;
            }
        }
block_64:
        temp_v1_7 = M2C_FIELD(work, s32 *, 0x1C);
        if (temp_v1_7 & 0x40000000) {
            M2C_FIELD(work, s32 *, 0x1C) = temp_v1_7 & 0xBFFFFFFF;
            temp_v0_3 = func_800BCB04(
                (M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20,
                (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20,
                (s16)(M2C_FIELD(work, u16 *, 0x88) - 0x20));
            if (temp_v0_3 < 0x200) {
                M2C_FIELD(arg0, s16 *, 0x92) = (u16)M2C_FIELD(arg0, s16 *, 0x92) +
                    (M2C_FIELD(work, u16 *, 0x88) - temp_v0_3);
                M2C_FIELD(work, u16 *, 0x88) = temp_v0_3;
            }
        }
        M2C_FIELD(arg1, s16 *, 0xA) = M2C_FIELD(arg0, u16 *, 0xAE) +
            (M2C_FIELD(work, u16 *, 0x88) + (u16)M2C_FIELD(arg0, s16 *, 0x92));
        M2C_FIELD(arg2, u16 *, 0x14) |= 0x40;
    }

#undef arg0
#undef arg1
#undef arg2
}

#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern int D_800814A8[4];
extern s32 D_800814A0;
void func_8002512C(void) __attribute__((noreturn));
void func_80025410() __attribute__((noreturn));
void func_80025594(void) __attribute__((noreturn));
M2C_UNK func_800257D0();
M2C_UNK func_80025840();
M2C_UNK func_8002590C();
M2C_UNK func_8002593C();
M2C_UNK func_80025B78();
M2C_UNK func_80025FCC();
s32 func_800644B8();
s32 func_80064584();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80065450();
M2C_UNK func_8009CE1C();
s32 func_800A07D0();
s32 func_800A45D8();
M2C_UNK func_800B653C();
extern s8 D_8002758C[];
extern u8 D_800287A2;
extern s32 D_800287A4;

void func_819AD81C(void *arg0_in, void *arg1_in, void *arg2_in) {
    typedef struct {
        s16 unk0;
        u16 unk2;
        s16 unk4;
        u16 unk6;
        s16 unk8;
        u16 unkA;
        s32 unkC;
        s32 unk10;
        s32 unk14;
    } Local20;
    typedef struct {
        s16 unk0;
        s16 unk2;
        s16 unk4;
    } Local38;
    Local20 sp20;
    Local38 sp38;
    M2C_UNK sp40;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v1_8;
    s32 temp_a1;
    s32 temp_v1_6;
    register s32 temp_v1_7 ASM_REG("$3");
    s32 var_v0_2;
    s8 temp_a0_2;
    s8 temp_v1_10;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u16 saved_x;
    u16 saved_y;
    void *var_s0;
    void *temp_a0;
    void *temp_s1;
    void *list_root;
    void *temp_v1_9;
    register void *arg0 ASM_REG("$18") = arg0_in;
    register void *arg1 ASM_REG("$19") = arg1_in;
    register void *arg2 ASM_REG("$20") = arg2_in;

    temp_v1_9 = M2C_FIELD(arg0, void **, 0x20);
    if (temp_v1_9 == 0) {
        temp_v0 = M2C_FIELD(arg0, s16 *, 0x2C);
        if (temp_v0 == 0) {
            temp_v1_2 = M2C_FIELD(arg2, u8 *, 0xC);
            temp_v1_3 = temp_v1_2 + ((s32) (0x80 - temp_v1_2) / M2C_FIELD(arg0, s16 *, 0x30));
            M2C_FIELD(arg2, u8 *, 0xC) = temp_v1_3;
            M2C_FIELD(arg2, u8 *, 0xD) = temp_v1_3;
            M2C_FIELD(arg2, u8 *, 0xE) = temp_v1_3;
            temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x30) - 1;
            M2C_FIELD(arg0, s16 *, 0x30) = temp_v0_2;
            if ((temp_v0_2 << 0x10) <= 0) {
                M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
                M2C_FIELD(arg0, u16 *, 0x2C) = (u16) (M2C_FIELD(arg0, u16 *, 0x2C) + 1);
                func_8002512C();
                return;
            }
            goto block_10;
        }
        if (temp_v0 >= 2) {
            temp_v1_4 = M2C_FIELD(arg2, u8 *, 0xC);
            temp_v1_5 = temp_v1_4 - ((s32) temp_v1_4 / (s16) M2C_FIELD(arg0, s16 *, 0x30));
            M2C_FIELD(arg2, u8 *, 0xC) = temp_v1_5;
            M2C_FIELD(arg2, u8 *, 0xD) = temp_v1_5;
            M2C_FIELD(arg2, u8 *, 0xE) = temp_v1_5;
            temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 0x30) - 1;
            M2C_FIELD(arg0, s16 *, 0x30) = temp_v0_3;
            if ((temp_v0_3 << 0x10) <= 0) {
                M2C_FIELD(arg2, s32 *, 0xC) = 0;
                func_80025410();
                return;
            }
            if (M2C_FIELD(arg0, s16 *, 0x2C) < 3) {
                goto block_10;
            }
        } else {
block_10:
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (func_80064584(M2C_FIELD(arg0, s16 *, 0x34)) << 8);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (func_800644B8(M2C_FIELD(arg0, s16 *, 0x34)) << 8);
            temp_a0_2 = M2C_FIELD(arg2, s8 *, 4);
            if (temp_a0_2 < 3) {
                temp_v1_6 = M2C_FIELD(arg1, s32 *, 0xC);
                M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v1_6 - (temp_v1_6 >> (temp_a0_2 + 1)));
                temp_v1_7 = M2C_FIELD(arg1, s32 *, 0x10);
                M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_v1_7 - (temp_v1_7 >> (M2C_FIELD(arg2, s8 *, 4) + 1)));
            }
            M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) - M2C_FIELD(arg1, s32 *, 0x14));
            M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
            M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
            M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
            M2C_FIELD(arg2, u16 *, 0x16) = 0x400U;
            M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (func_800A07D0(0, 0, M2C_FIELD(arg1, s16 *, 0xE), M2C_FIELD(arg1, s16 *, 0x12)) - 0x400);
            func_80025840(arg2, arg0 + 0x32, M2C_FIELD(arg0, s16 *, 0x38), M2C_FIELD(arg0, s16 *, 0x36));
            func_800257D0(arg0, M2C_FIELD(arg2, s32 *, 0));
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x4000) {
                M2C_FIELD(arg2, s8 *, 4) = 0;
            }
            if (M2C_FIELD(arg0, s16 *, 0x46) > 0) {
                M2C_FIELD(arg0, s16 *, 0x3C) = (s16) ((s16) M2C_FIELD(arg1, s16 *, 2) / 64);
                temp_a1 = (s16) M2C_FIELD(arg1, s16 *, 6) / 64;
                M2C_FIELD(arg0, s16 *, 0x3E) = (s16) temp_a1;
                if (M2C_FIELD(arg0, s32 *, 0x40) != M2C_FIELD(arg0, s32 *, 0x3C)) {
                    if ((func_800A45D8(((M2C_FIELD(arg0, s16 *, 0x3C) << 6) + 0x20) & 0xFFE0, ((temp_a1 << 6) + 0x20) & 0xFFE0, M2C_FIELD(arg1, s16 *, 0xA)) << 0x10) != 0) {
                        M2C_FIELD(arg0, s16 *, 0x30) = 4;
                        M2C_FIELD(arg0, s16 *, 0x2C) = 3;
                        func_80025594();
                        return;
                    }
                    ASM_SCHED_BARRIER();
                    var_s0 = (void *) D_800814A8[0];
                    list_root = var_s0;
                    temp_v1_9 = M2C_FIELD(var_s0, void **, 0x5C);
                    var_s0 = temp_v1_9 + 0x20;
                    if (var_s0 != list_root) {
                        do {
                            temp_s1 = M2C_FIELD(var_s0, void **, -0x14);
                            if (M2C_FIELD(temp_s1, u8 *, 0x24) == M2C_FIELD(arg0, s16 *, 0x3C)) {
                                if (M2C_FIELD(temp_s1, u8 *, 0x25) == M2C_FIELD(arg0, s16 *, 0x3E)) {
                                    var_v0_2 = M2C_FIELD(var_s0, s16 *, 0x88);
                                    temp_v1_7 = M2C_FIELD(arg1, s16 *, 0xA);
                                    var_v0_2 -= temp_v1_7;
                                    if (var_v0_2 < 0) {
                                        var_v0_2 = 0 - var_v0_2;
                                    }
                                    if (var_v0_2 < 0x40) {
                                        func_8009CE1C(var_s0, 0xC, D_800287A2, 0xA, (s32) (s16) (M2C_FIELD(arg0, u16 *, 0x44) << 9), D_800287A4, 2);
                                    }
                                }
                            }
                            var_s0 = M2C_FIELD(var_s0, s32 *, 0x5C) + 0x20;
                        } while (var_s0 != (void *) D_800814A8[0]);
                    }
                    saved_x = M2C_FIELD(arg0, u16 *, 0x3C);
                    temp_v1_8 = M2C_FIELD(arg0, u16 *, 0x46);
                    saved_y = M2C_FIELD(arg0, u16 *, 0x3E);
                    temp_v1_8 -= 1;
                    M2C_FIELD(arg0, s16 *, 0x46) = temp_v1_8;
                    M2C_FIELD(arg0, u16 *, 0x40) = saved_x;
                    M2C_FIELD(arg0, u16 *, 0x42) = saved_y;
                    if ((temp_v1_8 << 0x10) <= 0) {
                        M2C_FIELD(arg0, s16 *, 0x30) = 4;
                        M2C_FIELD(arg0, s16 *, 0x2C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1);
                    }
                    goto cleanup;
                }
                goto cleanup;
            }
cleanup:
            func_80025FCC(M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 6), M2C_FIELD(arg1, s16 *, 0xA), M2C_FIELD(arg0, s16 *, 0x34));
            func_80025B78(arg0, arg1, arg2);
            func_80025594();
        }
    } else {
        temp_a0 = (void *) ((s32) temp_v1_9 | 0x80000000);
        if (M2C_FIELD(temp_a0, u16 *, 0x1E) & 0x8000) {
            ASM_SCHED_BARRIER();
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0 |= 0x8000;
            func_80025594();
            return;
        }
        temp_v1_9 = M2C_FIELD(temp_a0, void **, 8);
        temp_s1 = M2C_FIELD(temp_a0, void **, 0xC);
        M2C_FIELD(arg1, s16 *, 2) = (s16) M2C_FIELD(temp_v1_9, u16 *, 2);
        M2C_FIELD(arg1, s16 *, 6) = (s16) M2C_FIELD(temp_v1_9, u16 *, 6);
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) M2C_FIELD(temp_v1_9, u16 *, 0xA);
        M2C_FIELD(arg2, u16 *, 0x16) = (u16) M2C_FIELD(temp_s1, u16 *, 0x16);
        M2C_FIELD(arg2, u16 *, 0x18) = (u16) M2C_FIELD(temp_s1, u16 *, 0x18);
        M2C_FIELD(arg2, u16 *, 0x1A) = (u16) M2C_FIELD(temp_s1, u16 *, 0x1A);
        M2C_FIELD(arg2, u16 *, 0x1C) = (u16) M2C_FIELD(temp_s1, u16 *, 0x1C);
        M2C_FIELD(arg2, u16 *, 0x1E) = (u16) M2C_FIELD(temp_s1, u16 *, 0x1E);
        M2C_FIELD(arg2, u16 *, 0x20) = (u16) M2C_FIELD(temp_s1, u16 *, 0x20);
        M2C_FIELD(arg2, s32 *, 0xC) = M2C_FIELD(temp_s1, s32 *, 0xC);
        temp_v1_10 = D_8002758C[M2C_FIELD(arg0, s16 *, 0x48)];
        var_s0 = temp_a0 + 0x20;
        if ((temp_v1_10 >= 0) && (M2C_FIELD(temp_s1, s8 *, 4) == temp_v1_10)) {
            func_800649A0(temp_a0);
            func_8002593C(arg0, arg1, arg2);
            sp38.unk0 = 0;
            sp38.unk2 = 0;
            sp38.unk4 = 0;
            func_80065450(&sp38, arg1 + 0xC, &sp40);
            func_80064A40();
            sp20.unk2 = (u16) M2C_FIELD(arg1, s32 *, 0xC);
            sp20.unk6 = (u16) M2C_FIELD(arg1, s32 *, 0x10);
            sp20.unkA = (u16) M2C_FIELD(arg1, s32 *, 0x14);
            sp20.unkC = func_80064584(M2C_FIELD(var_s0, s16 *, 0x34)) * 0x10;
            sp20.unk10 = func_800644B8(M2C_FIELD(var_s0, s16 *, 0x34)) * 0x10;
            sp20.unk14 = 0;
            func_800B653C(&sp20, M2C_FIELD(var_s0, s16 *, 0x34));
        }
        func_8002590C(arg2, M2C_FIELD(temp_s1, s8 *, 4));
        func_800257D0(arg0, M2C_FIELD(arg2, s32 *, 0));
    }
}

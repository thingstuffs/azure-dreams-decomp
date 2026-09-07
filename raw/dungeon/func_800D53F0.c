#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct WorkBlock {
    s16 *unk0;
    s16 *unk4;
    s32 unk8;
    u16 unkC;
    s32 unk10;
    s32 unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
} WorkBlock;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_800814A0[3];
extern s32 func_800644B8();
extern s32 func_80066460();
extern void func_800DBA90(WorkBlock *);
extern void func_800DABB0();
extern void func_800DAD60();
extern void func_800DADE4();
extern void func_800DAE18();

void func_800DAB50(void *arg0) {
    WorkBlock work;
    register void *var_s2 ASM_REG("$18") = arg0;
    register s32 var_s0 ASM_REG("$16");
    register s32 var_s1 ASM_REG("$17");
    register s32 var_a0_2 ASM_REG("$4");
    register s32 var_a1_2 ASM_REG("$5");
    register s32 temp_shifted ASM_REG("$3");
    register s32 temp_v0_2 ASM_REG("$2");
    s32 temp_v1;

    work.unk28 = 0;
    work.unk20 = 0;
    if (M2C_FIELD(var_s2, s16 *, 8) != 0) {
        work.unk22 = 0x30;
        work.unk2A = M2C_FIELD(var_s2, u16 *, 2) + 0x30;
        func_800DABB0();
        return;
    }
    temp_v0_2 = M2C_FIELD(var_s2, u16 *, 2);
    work.unk2A = 0x30;
    work.unk22 = (temp_v0_2 * 2) + 0x40;
    var_s0 = 0;
    work.unk24 = (s16)(func_800644B8(((s16)M2C_FIELD(var_s2, u16 *, 2) - 0x20) << 6) >> 6);
    work.unk0 = &work.unk20;
    work.unk2C = 0;
    work.unk18 = 2;
    temp_v0_2 = M2C_FIELD(var_s2, u16 *, 0xA);
    var_s1 = 0x28;
    work.unk8 = 0;
    work.unk14 = 0;
    work.unk10 = 0;
    work.unk1A = 0;
    work.unkC = temp_v0_2;
    do {
        work.unk4 = (s16 *)((s8 *)var_s2 + var_s1);
        func_800DBA90(&work);
        temp_v0_2 = work.unkC;
        ASM_KEEP(temp_v0_2);
        var_s0 += 1;
        work.unkC = temp_v0_2 + 0x200;
        var_s1 += 0x10;
    } while (var_s0 < 2);

    var_s0 = 3;
    {
        register s16 *p ASM_REG("$4") = (s16 *)((s8 *)var_s2 + 0x18);
        do {
            M2C_FIELD(p, u16 *, 0x28) = (u16)(M2C_FIELD(p, u16 *, 0x28) + M2C_FIELD(var_s2, u16 *, 0x20));
            M2C_FIELD(p, u16 *, 0x2A) = (u16)(M2C_FIELD(p, u16 *, 0x2A) + M2C_FIELD(var_s2, u16 *, 0x22));
            var_s0 -= 1;
            M2C_FIELD(p, u16 *, 0x2C) = (u16)(M2C_FIELD(p, u16 *, 0x2C) + M2C_FIELD(var_s2, u16 *, 0x24));
            p -= 4;
        } while (var_s0 >= 0);
    }

    temp_v1 = M2C_FIELD(var_s2, s16 *, 0);
    if (temp_v1 != 1) {
        if (temp_v1 < 2) {
            if (temp_v1 != 0) {
                func_800DADE4();
                return;
            }
            goto state_0;
        }
        if (temp_v1 != 2) {
            if (temp_v1 != 3) {
                func_800DADE4();
                return;
            }
            goto state_3;
        }
        goto state_2;
    }
    goto state_1;

state_0:
    M2C_FIELD(var_s2, s32 *, 0x10) = 0;
    M2C_FIELD(var_s2, s16 *, 4) = func_80066460(0, 1, 0x2C0, 0x100);
    M2C_FIELD(var_s2, s32 *, 0xC) = 0x242424;
    M2C_FIELD(var_s2, s16 *, 0) = (s16)((u16)M2C_FIELD(var_s2, s16 *, 0) + 1);
    goto state_1;

state_1:
    M2C_FIELD(var_s2, s32 *, 0x10) = M2C_FIELD(var_s2, s32 *, 0x10) + M2C_FIELD(var_s2, s32 *, 0xC);
    var_a0_2 = 0;
    if (M2C_FIELD(var_s2, u8 *, 0x13) != 0) {
        func_80066460(0, 3, 0x2C0, 0x100);
        func_800DAD60(var_a0_2, 0xFFFFFF);
        return;
    }
    goto block_27;

state_2:
    M2C_FIELD(var_s2, s32 *, 0x10) = M2C_FIELD(var_s2, s32 *, 0x10) - M2C_FIELD(var_s2, s32 *, 0xC);
    var_a0_2 = 0;
    if ((u8)M2C_FIELD(var_s2, s32 *, 0x10) == 0x7F) {
        temp_v0_2 = func_80066460(0, 3, 0x2C0, 0x100);
        var_a1_2 = 0xA0A0A0;
        var_a0_2 = 0x101010;
        temp_v1 = M2C_FIELD(var_s2, u16 *, 0);
        M2C_FIELD(var_s2, s16 *, 4) = temp_v0_2;
        M2C_FIELD(var_s2, s32 *, 0x10) = var_a1_2;
        ASM_KEEP(var_a1_2);
        M2C_FIELD(var_s2, s32 *, 0xC) = var_a0_2;
        temp_v1 += 1;
        M2C_FIELD(var_s2, s16 *, 0) = temp_v1;
        func_800DADE4((void *)var_a0_2, var_a1_2);
        return;
    }
    goto block_27;

state_3:
    var_a0_2 = M2C_FIELD(var_s2, s32 *, 0xC);
    var_a1_2 = var_a0_2;
    temp_shifted = M2C_FIELD(var_s2, s32 *, 0x10) - var_a0_2;
    M2C_FIELD(var_s2, s32 *, 0x10) = temp_shifted;
    if (var_a1_2 > 0x80808) {
        M2C_FIELD(var_s2, s32 *, 0xC) = var_a1_2 + 0xFFFEFEFF;
        ASM_KEEP(var_a1_2);
    }
    if (M2C_FIELD(var_s2, s32 *, 0x10) < 0) {
        M2C_FIELD(var_s2, s32 *, 0x10) = 0;
        M2C_FIELD(var_s2, u16 *, -2) = (u16)(M2C_FIELD(var_s2, u16 *, -2) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }

block_27:
    temp_v0_2 = M2C_FIELD(var_s2, volatile u16 *, 2);
    ASM_KEEP(temp_v0_2);
    temp_v0_2 <<= 0x10;
    temp_shifted = temp_v0_2 >> 0xE;
    temp_v0_2 >>= 0x11;
    var_s0 = temp_shifted + temp_v0_2;
    temp_v0_2 = M2C_FIELD(var_s2, s16 *, 8);
    temp_shifted = M2C_FIELD(var_s2, s16 *, 0xA);
    if (temp_v0_2 == 0) {
        temp_shifted -= var_s0;
        ASM_TAILSLOT_PIN(temp_shifted);
        func_800DAE18(var_a0_2);
        return;
    }
    temp_shifted += var_s0;
    ASM_KEEP(temp_shifted);
    temp_v0_2 = M2C_FIELD(var_s2, volatile u16 *, 2);
    M2C_FIELD(var_s2, u16 *, 0xA) = temp_shifted;
    M2C_FIELD(var_s2, u16 *, 2) = temp_v0_2 - 1;
}

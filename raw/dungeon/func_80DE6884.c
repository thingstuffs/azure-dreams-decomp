#include "common.h"
typedef s32 M2C_UNK;
typedef struct {
    s32 words[6];
} Copy24;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define NULL 0

M2C_UNK func_8003DB94();
s32 func_8003DE58(s32, void *, s16 *, s32);
void *func_8003FC64();
M2C_UNK func_8004491C();
M2C_UNK func_800478B8();
s32 func_800644B8();
s32 func_80064584(s32, s32);
s32 rand();
extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800DEA68[3];
extern M2C_UNK D_80173F8C[3];

void func_80DE6884(void *arg0, void *arg1, void *arg2) {
    u16 offsets[3];
    s32 copy0;
    s32 copy1;
    s32 copy2;
    s32 copy3;
    s32 copy4;
    s32 copy5;
    s32 temp_v1;
    register s32 var_s2 ASM_REG("$18");
    s32 var_v0;
    register void *held_arg1 ASM_REG("$21") = arg1;
    register void *held_arg0 ASM_REG("$19");
    register M2C_UNK *temp_s4 ASM_REG("$20");
    register u32 temp_v0_addr ASM_REG("$2");
    register void *setup_arg1 ASM_REG("$5");
    register s16 *setup_arg2 ASM_REG("$6");
    void *db_arg1;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;

    setup_arg1 = arg2;
    setup_arg2 = (s16 *)offsets;
    var_s2 = 0;
    offsets[2] = 0;
    offsets[1] = 0;
    offsets[0] = 0;
    held_arg0 = arg0;
    ASM_KEEP(setup_arg1);
    ASM_KEEP(setup_arg2);
    ASM_KEEP(var_s2);
    func_8003DE58(M2C_FIELD(setup_arg1, s32 *, 8), setup_arg1, setup_arg2, var_s2);
    temp_v0_addr = 0x80170000;
    ASM_KEEP(temp_v0_addr);
    temp_s4 = (M2C_UNK *)(temp_v0_addr + 0x3F8C);
    do {
        temp_v0 = func_8003FC64(0x212);
        if (temp_v0 != NULL) {
            db_arg1 = &D_800DEA68;
            temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = temp_s4;
            M2C_FIELD(temp_s0, s8 *, 0xE) = 0x60;
            M2C_FIELD(temp_s0, s8 *, 0xD) = 0x60;
            M2C_FIELD(temp_s0, s8 *, 0xC) = 0x60;
            M2C_FIELD(temp_s0, u16 *, 0x14) = (u16)(M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
            M2C_FIELD(temp_s0, u16 *, 0x10) = (u16)(M2C_FIELD(temp_s0, u16 *, 0x10) | 0x20);
            func_8003DB94(temp_s0, db_arg1, 0);
            func_800478B8(temp_s0);
            var_v0 = rand();
            temp_v1 = var_v0;
            if (temp_v1 < 0) {
                var_v0 = temp_v1 + 0xFFF;
            }
            M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16)(temp_v1 - ((var_v0 >> 0xC) << 0xC));
            M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
            func_8004491C(temp_v0, &D_80045340);
            temp_s0_2 = M2C_FIELD(temp_v0, void **, 8);
            copy0 = M2C_FIELD(held_arg1, s32 *, 0);
            copy1 = M2C_FIELD(held_arg1, s32 *, 4);
            copy2 = M2C_FIELD(held_arg1, s32 *, 8);
            copy3 = M2C_FIELD(held_arg1, s32 *, 0xC);
            M2C_FIELD(temp_s0_2, s32 *, 0) = copy0;
            M2C_FIELD(temp_s0_2, s32 *, 4) = copy1;
            M2C_FIELD(temp_s0_2, s32 *, 8) = copy2;
            M2C_FIELD(temp_s0_2, s32 *, 0xC) = copy3;
            copy4 = M2C_FIELD(held_arg1, s32 *, 0x10);
            copy5 = M2C_FIELD(held_arg1, s32 *, 0x14);
            M2C_FIELD(temp_s0_2, s32 *, 0x10) = copy4;
            M2C_FIELD(temp_s0_2, volatile s32 *, 0x14) = copy5;
            M2C_FIELD(temp_s0_2, u16 *, 2) = (u16)(M2C_FIELD(temp_s0_2, volatile u16 *, 2) + offsets[0]);
            M2C_FIELD(temp_s0_2, u16 *, 6) = (u16)(M2C_FIELD(temp_s0_2, u16 *, 6) + offsets[1]);
            M2C_FIELD(temp_s0_2, u16 *, 0xA) = (u16)(M2C_FIELD(temp_s0_2, u16 *, 0xA) + offsets[2]);
            M2C_FIELD(temp_s0_2, s32 *, 0xC) = (s32)((func_80064584(
                M2C_FIELD(held_arg0, s16 *, 0x2A),
                copy3) >> 4) << 0xB);
            M2C_FIELD(temp_s0_2, s32 *, 0x10) = (s32)((func_800644B8(M2C_FIELD(held_arg0, s16 *, 0x2A)) >> 4) << 0xB);
            M2C_FIELD(temp_s0_2, s32 *, 0x14) = 0x9C40;
        }
        var_s2 += 1;
    } while (var_s2 < 4);
    ASM_KEEP(held_arg1);
    ASM_KEEP(held_arg0);
    ASM_KEEP(var_s2);
    ASM_KEEP(temp_s4);
}

/* MECHANISM: One aliased three-halfword stack object and held s2-s5 roles reproduce the 0x38 frame.
   A grouped 24-byte scalar copy keeps its fourth word live in a1 for the two-argument callee ABI.
   Split v0-to-s4 page formation plus paired volatile store/read ordering closes the final rotations. */

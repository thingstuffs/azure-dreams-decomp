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

extern u8 D_80045340[];
extern u8 D_800DEC70[];
void *func_8003FC64();
s32 func_8004491C();
void func_8003DB94();
extern M2C_UNK D_800F68AC;

void func_8092192C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u16 temp_v0_2;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0;
    register void *temp_v1 ASM_REG("$3");
    register u32 temp_page ASM_REG("$5");
    s32 temp_input0;
    s32 temp_input4;
    s32 temp_input8;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800F68AC;
        func_8004491C(temp_v0, D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_a0, s16 *, 6) = 6;
        temp_v0_2 = M2C_FIELD(temp_a0, u16 *, 0x14);
        temp_v0_2 = temp_v0_2 | 0xC;
        M2C_FIELD(temp_a0, volatile u16 *, 0x14) = temp_v0_2;
        ASM_KEEP(temp_v0_2);
        temp_v0_2 = temp_v0_2 | 2;
        M2C_FIELD(temp_a0, volatile u16 *, 0x14) = temp_v0_2;
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        temp_input0 = (s32) M2C_FIELD(arg0, s32 *, 0);
        ASM_SCHED_BARRIER();
        temp_page = 0x800E0000;
        ASM_KEEP_DEP_NV(temp_page, temp_input0);
        M2C_FIELD(temp_v1, s32 *, 0) = temp_input0;
        temp_input4 = (s32) M2C_FIELD(arg0, s32 *, 4);
        ASM_KEEP_DEP_NV(temp_page, temp_input4);
        temp_page -= 5008;
        ASM_KEEP(temp_page);
        M2C_FIELD(temp_v1, volatile s32 *, 4) = temp_input4;
        temp_input8 = (s32) M2C_FIELD(arg0, s32 *, 8);
        M2C_FIELD(temp_v1, volatile u16 *, 2) = (u16) (M2C_FIELD(temp_v1, volatile u16 *, 2) + arg1);
        M2C_FIELD(temp_v1, s32 *, 8) = temp_input8;
        M2C_FIELD(temp_v1, u16 *, 6) = (u16) (M2C_FIELD(temp_v1, u16 *, 6) + arg2);
        M2C_FIELD(temp_v1, u16 *, 0xA) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xA) + arg3);
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_2, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_a0_2, s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_a0_2, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xC) = 0x80;
        func_8003DB94(temp_a0_2, (void *) temp_page, 0);
    }
}

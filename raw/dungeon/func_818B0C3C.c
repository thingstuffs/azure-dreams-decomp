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

void func_800245EC(void) __attribute__((noreturn));
M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_800644B8();
s32 func_80064584();
s32 func_80069EF8();
extern M2C_UNK D_800242E0;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEC70;

s32 func_8002443C(s32 arg0, void *arg1, s16 arg2, s32 arg3) {
    u16 copy_value;
    u16 final_value;
    s32 var_s0;
    M2C_UNK *node_type;
    void *temp_s0;
    register s32 return_v0 ASM_REG("$2");
    register u8 *work_s1 ASM_REG("$17") = (u8 *)arg0;
    register u8 *work_s2 ASM_REG("$18") = (u8 *)arg1;
    register s16 work_s0 ASM_REG("$16") = arg2;
    register u8 *work_s3 ASM_REG("$19");
    register s32 work_s4 ASM_REG("$20") = arg3;
    register s32 init_value ASM_REG("$3");

    work_s3 = func_8003FC64(0x212);
    ASM_KEEP(work_s1);
    ASM_KEEP(work_s2);
    ASM_KEEP(work_s0);
    ASM_KEEP(work_s4);
    if (work_s3 != NULL) {
        node_type = &D_800242E0;
        ASM_USE(node_type);
        M2C_FIELD(work_s3, s32 *, 0x20) = (s32)work_s1;
        work_s1 = work_s3 + 0x20;
        M2C_FIELD(work_s3, M2C_UNK **, 0x10) = node_type;
        M2C_FIELD(work_s1, s16 *, 4) = work_s0;
        M2C_FIELD(work_s1, s16 *, 6) = (s16) (-6 - (func_80069EF8() % 5));
        M2C_FIELD(work_s1, u16 *, 8) = (u16) M2C_FIELD(work_s2, u16 *, 2);
        M2C_FIELD(work_s1, u16 *, 0xA) = (u16) M2C_FIELD(work_s2, u16 *, 6);
        copy_value = M2C_FIELD(work_s2, u16 *, 0xA);
        ASM_KEEP(copy_value);
        init_value = 0x7E09;
        ASM_USE(init_value);
        M2C_FIELD(work_s1, u16 *, 0xC) = copy_value;
        temp_s0 = M2C_FIELD(work_s3, void **, 0xC);
        M2C_FIELD(temp_s0, s8 *, 0xE) = 0;
        M2C_FIELD(temp_s0, s8 *, 0xD) = 0;
        M2C_FIELD(temp_s0, s8 *, 0xC) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x12) = (s16)init_value;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x10) | 0x20);
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
        func_8003DB94(temp_s0, &D_800DEC70, (s16)work_s4 % 16, (s16)work_s4);
        ASM_USE(work_s4);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        func_8004491C(work_s3, &D_80045340);
        work_s2 = M2C_FIELD(work_s3, void **, 8);
        ASM_KEEP(work_s3);
        var_s0 = func_80069EF8() % 0x1000;
        M2C_FIELD(work_s2, s16 *, 2) = (s16) (M2C_FIELD(work_s1, u16 *, 8) + ((s32) (func_800644B8(var_s0) * 2) >> 8));
        M2C_FIELD(work_s2, s16 *, 6) = (s16) (M2C_FIELD(work_s1, u16 *, 0xA) + ((s32) (func_80064584(var_s0) * 2) >> 8));
        final_value = M2C_FIELD(work_s1, u16 *, 0xC);
        ASM_USE(final_value);
        return_v0 = (s32)work_s3;
        ASM_KEEP(return_v0);
        M2C_FIELD(work_s2, s16 *, 0xA) = (s16)final_value;
        func_800245EC();
    }
    return_v0 = 0;
    ASM_KEEP(return_v0);
    return return_v0;
}

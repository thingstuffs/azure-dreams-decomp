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
extern u8 D_80083498[];
extern u8 D_800DEC70[];
void *func_8003FC64();
s32 func_8004491C();
extern u8 D_800F6000[];
extern M2C_UNK D_800F6A44;

void func_80921B2C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[32];
    u8 *temp_source;
    register s32 saved_arg2 ASM_REG("$20") = arg2;
    register s32 saved_arg3 ASM_REG("$21") = arg3;
    u16 temp_v0_2;
    register s32 temp_call_arg ASM_REG("$4");
    register u8 *temp_page ASM_REG("$2");
    register u8 *temp_s6 ASM_REG("$22");
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_v0;

    temp_source = D_800F6000;
    ASM_SCHED_BARRIER();
    memcpy(sp, temp_source, 0x20);
    temp_call_arg = 0x212;
    ASM_USE_NV(temp_call_arg);
    temp_page = D_80083498;
    temp_s6 = temp_page + 0x20;
    temp_v0 = func_8003FC64(temp_call_arg);
    if (temp_v0 != NULL) {
        u8 *temp_buf = sp;

        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800F6A44;
        func_8004491C(temp_v0, D_80045340);
        {
            register void *temp_a0 ASM_REG("$4");

            temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
            temp_v0_2 = M2C_FIELD(temp_a0, u16 *, 0x14);
            ASM_USE(temp_v0_2);
            M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_a0, s16 *, 6) = 6;
            ASM_SCHED_BARRIER();
            temp_v0_2 |= 0xC;
            M2C_FIELD(temp_a0, volatile u16 *, 0x14) = temp_v0_2;
            temp_v0_2 |= 2;
            M2C_FIELD(temp_a0, volatile u16 *, 0x14) = temp_v0_2;
        }
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0_2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
        M2C_FIELD(temp_a0_2, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
        M2C_FIELD(temp_a0_2, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 8);
        M2C_FIELD(temp_a0_2, u16 *, 2) = (u16) (M2C_FIELD(temp_a0_2, u16 *, 2) + arg1);
        M2C_FIELD(temp_a0_2, u16 *, 6) = (u16) (M2C_FIELD(temp_a0_2, u16 *, 6) + saved_arg2);
        M2C_FIELD(temp_a0_2, u16 *, 0xA) = (u16) (M2C_FIELD(temp_a0_2, u16 *, 0xA) + saved_arg3);
        M2C_FIELD(temp_a0_2, s32 *, 0xC) = (s32) (M2C_FIELD(temp_buf, s16 *, (((u16) M2C_FIELD(temp_s6, volatile u16 *, 0x2A) >> 7) & 0x1C)) * 0x180000);
        M2C_FIELD(temp_a0_2, s32 *, 0x10) = (s32) ((s16) M2C_FIELD((s8 *)temp_buf + (((u16) M2C_FIELD(temp_s6, volatile u16 *, 0x2A) >> 7) & 0x1C), u16 *, 2) * 0x180000);
        temp_a0_3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_3, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_a0_3, s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_a0_3, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0_3, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0_3, u8 *, 0xC) = 0x80;
        func_8003DB94(temp_a0_3, D_800DEC70, 0);
    }
}

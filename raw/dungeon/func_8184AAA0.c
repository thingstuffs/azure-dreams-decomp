#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80024354(void) __attribute__((noreturn));
M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80024224;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE8E8;

void *func_800242A0(s32 arg0, void *arg1) {
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 == NULL) {
        register void *zero ASM_REG("$2") = NULL;

        ASM_TAILSLOT_PIN(zero);
        func_80024354();
    }
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024224;
    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = arg0;
    M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
    func_8003DB94(temp_s0, &D_800DE8E8, 0);
    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
    func_8004491C(temp_v0, &D_80045340);
    temp_v1 = M2C_FIELD(temp_v0, void **, 8);
    M2C_FIELD(temp_v1, u16 *, 2) = (u16)M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(temp_v1, u16 *, 6) = (u16)M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(temp_v1, u16 *, 0xA) = (u16)M2C_FIELD(arg1, u16 *, 0xA);
    return temp_v0;
}

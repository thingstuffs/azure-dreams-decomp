#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8003E4FC();
extern s32 func_80049984();
extern s16 func_800B6CEC();
extern M2C_UNK func_800B6D54();
extern M2C_UNK func_800B6D94();
extern s32 func_800B6F40();
extern s32 func_800B6F54();
extern s16 D_80083D78[8];
extern u8 D_800B5B20[16];

s32 func_800B6E3C(void *arg0) {
    s32 temp_v0;
    s32 temp_idx;
    void *temp_a0;
    register s32 tail_value ASM_REG("$2");

    M2C_FIELD(arg0, s16 *, 0xA) = func_800B6CEC(M2C_FIELD(arg0, s32 *, 4));
    temp_v0 = func_80049984(M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(arg0, s32 *, 0x10) = temp_v0;
    if (temp_v0 == 3) {
        M2C_FIELD(arg0, s32 *, 0x10) = 0;
    }
    if (func_800B6F54(arg0) != 0) {
        *((M2C_FIELD(arg0, s16 *, 8) * 2) + D_80083D78) = -1;
    }
    temp_a0 = (M2C_FIELD(arg0, s16 *, 8) * 2) + D_80083D78;
    if ((M2C_FIELD(temp_a0, s16 *, 0) != M2C_FIELD(arg0, s16 *, 0xA)) || (M2C_FIELD(temp_a0, s16 *, 2) != M2C_FIELD(arg0, s32 *, 0x10))) {
        M2C_FIELD(temp_a0, s16 *, 0) = -1;
        temp_idx = M2C_FIELD(arg0, s16 *, 8);
        temp_idx <<= 2;
        temp_idx += (s32)D_80083D78;
        M2C_FIELD((void *)temp_idx, s16 *, 2) = -1;
        func_800B6D94(M2C_FIELD(arg0, s32 *, 0x14), &D_80083D78);
        M2C_FIELD(arg0, s32 *, 0xDC) = 0;
        func_800B6D54(arg0);
        M2C_FIELD(arg0, s32 *, 0xD0) = func_8003E4FC(6, arg0 + 0xD8, NULL);
        M2C_FIELD(arg0, s32 *, 0xD4) = func_8003E4FC(0xFF, &D_800B5B20, arg0);
        tail_value = 1;
        ASM_TAILSLOT_PIN(tail_value);
        return func_800B6F40();
    }
    return 0;
}

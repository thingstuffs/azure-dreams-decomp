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

extern M2C_UNK func_800250B4();
extern void *func_80025350();
extern M2C_UNK func_800253C0();
extern s32 func_80026168();
extern s32 func_80026A64();
extern s32 func_8002845C();
extern void *func_8003FC64();
extern s32 func_8004A330();
extern M2C_UNK func_800DBF38();
extern s32 D_80029498;
extern s32 D_800814A0;
extern u8 D_80082E6A;

void *func_80025198(s32 arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4) {
    s32 *temp_s0;
    register s32 temp_a0 ASM_REG("$4");
    s32 var_a0;
    void *temp_a1;
    void *temp_s2;
    s32 *temp_s5;
    void *temp_v0;
    void *var_v1;

    temp_v0 = func_8003FC64(0);
    if (temp_v0 != NULL) {
        temp_a1 = arg3;
        temp_s2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg0;
        M2C_FIELD(temp_s2, s32 *, 0x10) = arg1;
        M2C_FIELD(temp_s2, s32 *, 0x14) = (s32) M2C_FIELD(temp_a1, u8 *, 1);
        M2C_FIELD(temp_s2, s32 *, 0x18) = arg2;
        M2C_FIELD(temp_s2, s32 *, 0x1C) = (s32) M2C_FIELD(temp_a1, u8 *, 0);
        func_800250B4(temp_s2, temp_a1, arg4);
        M2C_FIELD(temp_v0, s32 *, 0x10) = 0;
        temp_a0 = 8;
        if (D_80082E6A != 1) {
            func_800DBF38();
            temp_a0 = 8;
        }
        temp_s0 = &D_80029498;
        M2C_FIELD(temp_s2, s32 *, 0x2C) = func_8004A330(temp_a0, 0xEC, 0x64, 0xEC, 0x64, 0x50, 1, D_80029498);
        M2C_FIELD(temp_s2, s32 *, 0x30) = func_8004A330(4, 0xEC, 0x64, 0xEC, 0x74, 0x50, 1, M2C_FIELD(temp_s0, s32 *, 4));
        M2C_FIELD(temp_s2, s32 *, 0x34) = func_8004A330(0x10, 0xEC, 0x64, 0xEC, 0x84, 0x50, 1, M2C_FIELD(temp_s0, s32 *, 8));
        M2C_FIELD(temp_s2, s32 *, 0x20) = func_80026168(temp_v0, M2C_FIELD(temp_s2, s32 *, 0x14), M2C_FIELD(temp_s2, s32 *, 4));
        M2C_FIELD(temp_s2, s32 *, 0x24) = func_8002845C(temp_v0, M2C_FIELD(temp_s2, s32 *, 0x14));
        M2C_FIELD(temp_s2, s32 *, 0x28) = func_80026A64(temp_v0, M2C_FIELD(temp_s2, s32 *, 0x14), M2C_FIELD(temp_s2, s32 *, 4));
        temp_s5 = (s32 *) 0x80080000;
        var_a0 = 0;
        var_v1 = temp_s2;
loop_4:
        var_a0 += 1;
        if (M2C_FIELD(var_v1, s32 *, 0x20) != 0) {
            goto nonzero;
        }
        func_800253C0(temp_s2);
        M2C_FIELD(temp_s2, u16 *, -2) = (u16) (M2C_FIELD(temp_s2, u16 *, -2) | 0x8000);
        temp_v0 = NULL;
        M2C_FIELD(temp_s5, s32 *, 0x14A0) |= 0x8000;
        goto end;
nonzero:
        var_v1 += 4;
        if (var_a0 < 3) {
            goto loop_4;
        }
    }
end:
    return temp_v0;
}

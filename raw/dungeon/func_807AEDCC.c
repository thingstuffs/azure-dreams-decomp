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
#define M2C_UNALIGNED32(expr) (expr)

struct S_8003E2D8 {
    u8 pad0[0x1DC];
    s32 *field_1DC;
    s16 pad_1E0[8];
    s16 field_1F0;
};
typedef struct S_8003E2D8 S_8003E2D8;
struct S_80082E60 {
    u8 pad0[0x10];
    s16 field_10;
    s16 field_12;
    s16 field_14;
    s16 field_16;
};
typedef struct S_80082E60 S_80082E60;
extern s16 *D_800F8A44[];
extern struct S_8003E2D8 D_80083160;
extern struct S_80082E60 D_80082E60;
extern volatile s16 D_80013714[8];
extern u8 D_80013720[];
extern u8 D_800F6544[];
extern u8 D_800F8A4C[];
struct S_10 {
    u8 data[10];
};
void *func_8003FC64(s32, s32, s16 **, s32);

void func_800F65CC(void) {
    s16 **var_a2;
    s16 *temp_v0;
    s32 temp_s0;
    s32 var_a1;
    S_8003E2D8 *base;
    s16 *s1;
    S_80082E60 *a0;
    s16 **table;
    s32 a3;
    u16 temp_v0_3;
    void *temp_v0_2;
    void *temp_v1;

    base = &D_80083160;
    s1 = (s16 *)((u8 *)base + 0x1DC);
    temp_s0 = base->field_1DC;
    var_a1 = 1;
    a3 = 0x11;
    table = D_800F8A44;
    var_a2 = table + 1;
    a0 = &D_80082E60;
    a0->field_10 = 0x1F;
    a0->field_12 = 0x3E;
    a0->field_16 = (u16)(a0->field_16 | 1);
    do {
        temp_v0 = *var_a2;
        if (temp_v0 != NULL) {
            *temp_v0 = a3;
        }
        var_a1 -= 1;
        var_a2 -= 1;
    } while (var_a1 >= 0);
    temp_v0_2 = func_8003FC64(0x12, var_a1, var_a2, a3);
    if (temp_v0_2 != NULL) {
        s16 *status;

        M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_800F6544;
        M2C_FIELD(temp_v0_2, s16 *, 0x24) = 0x38;
        status = (s16 *)0x80010000;
        if (!((u16)status[0x3714 / 2] & 1)) {
            *(struct S_10 *)((u32)0x80010000 | 0x3720) = *(struct S_10 *)D_800F8A4C;
            status[0x371A / 2] = 0;
            status[0x3718 / 2] = 0;
            status[0x3716 / 2] = 4;
            status[0x3714 / 2] = (u16)(status[0x3714 / 2] | 1);
        }
    }
    var_a1 = 0x1E;
    do {
        temp_v1 = ((var_a1 + (0x3E << M2C_FIELD(s1, s16 *, 0x14))) * 6) + temp_s0;
        temp_v0_3 = M2C_FIELD(temp_v1, u16 *, 4);
        var_a1 += 1;
        M2C_FIELD(temp_v1, s16 *, 4) = (s16)(temp_v0_3 | 0x8000);
    } while (var_a1 < 0x21);
}

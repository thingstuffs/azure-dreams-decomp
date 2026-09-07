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

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Copy4;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80083498[];
extern void *D_80170898[];
extern u8 D_80045340[];
extern s16 D_80083228[5];
extern M2C_UNK D_80173EB4;
extern s32 func_8003DE58();
extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern M2C_UNK func_80047784();

void func_80170B50(void *arg0, void *arg1, void *arg2, s16 arg3) {
    u32 temp_v0_2;
    u16 temp_v1_2;
    s16 temp_s6;
    void *temp_a1;
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_v0;
    void *var_a2;
    void *var_a3;

    temp_s6 = arg3;
    temp_v0 = func_8003FD64(0x112, D_80083498);
    if (temp_v0 != NULL) {
        temp_s2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, void ***, 0x10) = D_80170898;
        M2C_FIELD(temp_s2, s16 *, 0xB6) = arg3;
        M2C_FIELD(temp_s2, s32 *, 0xAC) = (s32) (arg0 - 0x20);
        M2C_FIELD(temp_s2, u16 *, 0x94) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
        var_a3 = arg2;
        M2C_FIELD(temp_s2, u16 *, 0x2A) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        var_a2 = temp_s1;
        do {
            *(Copy4 *)var_a2 = *(Copy4 *)var_a3;
            var_a3 += 0x10;
            var_a2 += 0x10;
        } while (var_a3 != (arg2 + 0x30));
        func_8004491C(temp_v0, D_80045340, var_a2, var_a3);
        M2C_FIELD(temp_s1, M2C_UNK **, 0x2C) = &D_80173EB4;
        func_80047784(temp_s1, *((u8 *)&D_80173EB4 + ((((s32) (*D_80083228 + (s16) M2C_FIELD(arg0, u16 *, 0x2A) + 0x100) >> 9) & 7))), 0);
        M2C_FIELD(temp_s1, s16 *, 0x10) = 0x20;
        temp_v0_2 = M2C_FIELD(temp_s1, u16 *, 0x14) | 0xC;
        M2C_FIELD(temp_s1, u16 *, 0x14) = temp_v0_2;
        *(volatile u16 *)((s8 *)temp_s1 + 0x14) = temp_v0_2 | 0x80;
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_s0, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
        temp_a1 = M2C_FIELD(arg0, void **, -0x14);
        if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, temp_s2 + 0xB0, temp_s6) != 0) {
            M2C_FIELD(temp_s0, u16 *, 2) = (u16) (M2C_FIELD(temp_s0, u16 *, 2) + M2C_FIELD(temp_s2, u16 *, 0xB0));
            M2C_FIELD(temp_s0, u16 *, 6) = (u16) (M2C_FIELD(temp_s0, u16 *, 6) + M2C_FIELD(temp_s2, u16 *, 0xB2));
            M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xA) + M2C_FIELD(temp_s2, u16 *, 0xB4));
        }
        M2C_FIELD(temp_s1, u16 *, 0x1C) = (u16) M2C_FIELD(arg2, u16 *, 0x1C);
        temp_v1_2 = (u16) M2C_FIELD(arg2, u16 *, 0x1E);
        M2C_FIELD(temp_s1, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s1, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s1, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s1, u16 *, 0x1E) = temp_v1_2;
    }
}

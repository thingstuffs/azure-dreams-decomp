#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
typedef s32 M2C_UNK;
#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004491C();
extern M2C_UNK D_80046398;
extern M2C_UNK D_800A24A8;
extern M2C_UNK D_800D0A48;

void func_800A23D0(void *arg0, void *arg1, void *arg2) {
    M2C_UNK *table;
    M2C_FIELD(arg2, s32 *, 0) = 0;
    M2C_FIELD(arg2, s8 *, 4) = 0;
    M2C_FIELD(arg2, s8 *, 5) = 0;
    func_8004491C(arg0 - 0x20, &D_80046398);
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s32 *, 0);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s32 *, 4);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s32 *, 8);
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_800A24A8;
    table = &D_800D0A48;
    M2C_FIELD(arg2, s32 *, 8) = (s32) table[M2C_FIELD(arg0, s16 *, 0x20)];
    M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + 0x28);
    M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) - 8);
    M2C_FIELD(arg2, s16 *, 0x1A) = 0;
}

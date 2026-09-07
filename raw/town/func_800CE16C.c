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

M2C_UNK D_800CB9B8();               /* extern (function symbol used as callback) */
void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();              /* extern */
s32 func_800CB990();                   /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern s32 D_800D68B0[];

s32 func_800CB8CC(s32 arg0, s32 arg1) {
    s32 temp_s2;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x136, &D_80083498);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_s1 = temp_v0 + 0x20;
    temp_s2 = M2C_FIELD(temp_v0, s32 *, 8);
    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_s1, s32 *, 0x9C) = arg0;
    M2C_FIELD(temp_v0, M2C_UNK (**)(void *, s32, void *), 0x10) = D_800CB9B8;
    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_s0, s32 *, 0xC) = 0x808080;
    M2C_FIELD(temp_s1, s32 *, 0x60) = arg1;
    M2C_FIELD(temp_s0, s32 *, 8) = D_800D68B0[arg1];
    func_8004491C(temp_v0, &D_80045340);
    M2C_FIELD(temp_v0, M2C_UNK (**)(void *, s32, void *), 0x10)(temp_s1, temp_s2, temp_s0);
    func_800CB990();
    return (s32)temp_v0;
}

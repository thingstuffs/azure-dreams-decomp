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

M2C_UNK func_800985F4();
M2C_UNK func_80099754();
extern M2C_UNK D_800984AC;

void func_80098544(void *arg0, void *arg1) {
    register void *out ASM_REG("$5");
    s16 remaining;
    register s32 temp_v1 ASM_REG("$3");
    u16 temp_v0;
    register s32 temp_v2 ASM_REG("$2");

    out = arg1;
    ASM_KEEP(out);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0;
    if ((s16) temp_v0 > 0) {
        temp_v1 = M2C_FIELD(out, s32 *, 0);
        M2C_FIELD(out, s32 *, 0) = (s32) (temp_v1 + ((s32) ((M2C_FIELD(arg0, s16 *, 0x36) << 0x10) - temp_v1) / (s16) temp_v0));
        temp_v2 = M2C_FIELD(arg0, s16 *, 0x38);
        temp_v1 = M2C_FIELD(out, s32 *, 4);
        remaining = M2C_FIELD(arg0, s16 *, 0xA);
        M2C_FIELD(out, s32 *, 4) = (s32) (temp_v1 + ((s32) ((temp_v2 << 0x10) - temp_v1) / remaining));
        func_800985F4(remaining);
        return;
    }
    M2C_FIELD(out, s32 *, 0) = (s32) (M2C_FIELD(arg0, s16 *, 0x36) << 0x10);
    M2C_FIELD(out, s32 *, 4) = (s32) (M2C_FIELD(arg0, s16 *, 0x38) << 0x10);
    func_80099754(out);
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_800984AC;
}

#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800644B8(s32);
extern void func_800C4174(void);
extern void func_800C4EF0(void);

void func_800C4E30(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x6C) - 1;
    M2C_FIELD(arg0, s16 *, 0x6C) = temp_v0;
    if (temp_v0 <= 0) {
        M2C_FIELD(arg2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(arg2, s16 *, 0x1C) = 0x1000;
        func_800C4174();
        func_800C4EF0();
        return;
    }
    var_v0 = func_800644B8(temp_v0 * 0x199);
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    var_v1 = var_v0 >> 2;
    M2C_FIELD(arg2, s16 *, 0x1C) = (s16) (0x1000 - var_v1);
    var_v0_2 = func_800644B8(M2C_FIELD(arg0, s16 *, 0x6C) * 0x199);
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    M2C_FIELD(arg2, s16 *, 0x1E) = (s16) ((var_v0_2 >> 2) + 0x1000);
}

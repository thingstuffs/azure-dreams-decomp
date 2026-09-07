#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8009A3D0();

void func_800AA888(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 call_arg0;
    u8 call_arg1;
    M2C_UNK var_v1;

    M2C_FIELD(arg0, s8 *, 0x9A) = 0xB;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    call_arg0 = M2C_FIELD(arg2, u8 *, 0x24);
    call_arg1 = M2C_FIELD(arg2, u8 *, 0x25);
    var_v1 = 0x3000;
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
        var_v1 = 0x300;
    }
    func_8009A3D0(call_arg0, call_arg1, var_v1);
    M2C_FIELD(arg0, u16 *, 0x98) = (u16)(M2C_FIELD(arg0, u16 *, 0x98) | 8);
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32)(M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
    M2C_FIELD(arg0, s16 *, 0x96) = 0;
    M2C_FIELD(arg3, u16 *, 0x6A) = (u16)M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), u16 *, 0x2A);
}

/* MECHANISM: Named u8 call-argument locals force both byte loads before the flag branch,
   freeing v1 to carry the selected third argument into the jal delay slot.
   Natural arg0/arg3 lifetimes yield the exact 0x20 frame and s0/s1 save order. */

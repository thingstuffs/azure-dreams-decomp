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

void func_8009C93C(void *, void *, s16, s32, s32);
s32 func_800A0134(s32, void *);
s32 func_800A04F0(void *, u8, u8, s16);
s32 func_800A2B5C(void *);
s32 func_800A2CB8(void *, s32);
void func_800C7930(void *, s32, s32, s32);
void func_80175F44(void *, s32, void *, s32, s32);
extern s32 D_80083460;

s32 func_80172BB0(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    register s32 temp_v0 ASM_REG("$17");
    register s32 var_v0 ASM_REG("$19");
    register u16 *global ASM_REG("$20");

    {
        register s32 history ASM_REG("$2");

        history = M2C_FIELD(arg3, u8 *, 0x71);
        history &= 0x7F;
        M2C_FIELD(arg3, u8 *, 0x71) = history;
    }
    {
        register u8 *page ASM_REG("$2");

        page = (u8 *)0x80080000;
        ASM_KEEP(page);
        global = (u16 *)(page + 0x3460);
    }
    var_v0 = 0;
    if (global[1] & 0x2000) {
        return -1;
    }
    ASM_USE_NV(var_v0);

    temp_v0 = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24),
        M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A));
    if ((func_800A2CB8(arg3, temp_v0) << 0x10) == 0) {
        return var_v0;
    }

    if (global[1] & 0x2000) {
        return -1;
    }
    if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) && (global[1] & 8)) {
        return -1;
    }
    if ((u32)(((0 - func_800A0134(temp_v0, arg3)) + 0x40) & 0xFFFF) <
            0x81U) {
        var_v0 = 1;
        if ((func_800A2B5C(arg3) << 0x10) != 0) {
            return -1;
        }
        func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) != 0) {
            return -1;
        }

        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        if (M2C_FIELD(arg0, u8 *, 0xB5) == 0) {
            M2C_FIELD(arg0, s8 *, 0x9A) = 0x11;
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            M2C_FIELD(arg3, s8 *, 0x84) = 0x7C;
            M2C_FIELD(arg3, s8 *, 0x85) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) =
                (u16)(M2C_FIELD(arg0, u16 *, 0x98) | 8);
            func_8009C93C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1, 0);
            M2C_FIELD(arg3, u8 *, 0x6D)--;
        } else {
            register s32 one ASM_REG("$2");

            one = 1;
            func_80175F44(arg0, arg1, arg2, one, one);
        }
    }
    ASM_KEEP(var_v0);
    return var_v0;
}

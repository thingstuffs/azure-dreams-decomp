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

typedef struct DungeonSlot {
    u8 pad_00[0x1C];
    u32 flags;
} DungeonSlot;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800941D8();
M2C_UNK func_80094E34();
M2C_UNK func_8009A21C();
M2C_UNK func_8009A3D0();
s32 func_8009B88C();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern DungeonSlot *D_800E3DF0[];

s32 func_8009402C(void *arg0, void *arg1, void *arg2, s16 *arg3, s16 *arg4, void *arg5) {
    register s32 shifted_result ASM_REG("$2");
    s16 temp_a2;
    s16 temp_s0;
    s16 temp_s1;
    s16 temp_v0;
    s32 temp_s0_2;
    s32 temp_v1;
    s32 var_v0;
    s16 *coord_arg;
    void *tail_base;
    void *temp_v0_2;
    void *temp_v0_3;

    tail_base = arg0;
    coord_arg = arg3;
    if (arg5 != NULL) {
        var_v0 = 3;
        ASM_CLOBBER("$7");
        if (!(D_800E3DF0[M2C_FIELD(arg5, u8 *, 3) & 0x1F]->flags & 0x04000000)) {
            temp_v1 = ((u16) M2C_FIELD(arg0, u16 *, 0x2A) >> 8) & 0xE;
            temp_v0 = M2C_FIELD(arg2, u8 *, 0x24) + *(u16 *)(&D_8006CCD8 + temp_v1);
            temp_a2 = M2C_FIELD(arg2, u8 *, 0x25) + *(u16 *)(&D_8006CCE8 + temp_v1);
            if (((func_8009B88C(0, temp_v0, temp_a2, coord_arg, arg4) << 0x10) == 0) || ((M2C_FIELD(arg0, s32 *, 0x1C) & 0x100000) && (temp_v0_2 = M2C_FIELD(arg0, void **, 0x124), (temp_v0_2 != NULL)) && (M2C_FIELD(temp_v0_2, s8 *, 0x13) > 0) && (temp_s0 = *coord_arg, temp_s1 = *arg4, func_8009A21C(temp_s0, temp_s1, 0x8000), temp_s0_2 = func_8009B88C(0, temp_v0, temp_a2, coord_arg, arg4), func_8009A3D0(temp_s0, temp_s1, 0x8000), (shifted_result = temp_s0_2 << 0x10, shifted_result == 0)))) {
                func_800941D8();
                return 1;
            }
            goto block_9;
        }
        return var_v0;
    }
block_9:
    temp_v0_3 = M2C_FIELD(((M2C_FIELD(tail_base, s16 *, 0x8A) * 4) + arg0), void **, 0xAC);
    if ((temp_v0_3 != NULL) && !(M2C_FIELD(temp_v0_3, s32 *, 0x1C) & 0x20000)) {
        return 2;
    }
    func_80094E34();
    return 0;
}

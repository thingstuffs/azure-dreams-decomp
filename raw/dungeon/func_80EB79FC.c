#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern void *D_80170858[];
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A2FE0();
M2C_UNK func_800A32A4();
M2C_UNK func_800A56E0();
M2C_UNK func_800ACF88();
s16 func_800BCB04();
M2C_UNK func_80173494() __attribute__((noreturn));
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0[3];
extern M2C_UNK D_80083460;
extern s16 D_8008346A;

void func_801731FC(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    M2C_UNK var_a2;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v1;
    s32 temp_v1_2;
    u16 temp_v0_2;
    u32 temp_a1;
    u32 sound_x;
    u32 sound_y;
    u8 temp_v0;
    void *global_ptr;

    temp_a1 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_v1 = ((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE;
    temp_a2 = *(s16 *)((u8 *)&D_8006CCD8 + temp_v1);
    temp_a3 = *(s16 *)((u8 *)&D_8006CCE8 + temp_v1);
    if (temp_a1 >= 5U) {
        goto block_20;
    }
    (void)jt_keep;
    goto *D_80170858[(u32)temp_a1];
jt_c0:
    {
        u32 mask_a0 = 0xF7FFFFFF;
        u32 mask_v1;
        u32 flags;
        u16 field98;

        
        field98 = M2C_FIELD(arg0, u16 *, 0x98);
        
        mask_v1 = 0xFFFBFFFF;
        field98 |= 8;
        M2C_FIELD(arg0, u16 *, 0x98) = field98;
        flags = M2C_FIELD(arg3, u32 *, 0x1C);
        flags &= mask_a0;
        flags &= mask_v1;
        M2C_FIELD(arg3, u32 *, 0x1C) = flags;
        M2C_FIELD(arg1, s32 *, 0xC) = temp_a2 << 0x10;
        M2C_FIELD(arg1, s32 *, 0x10) = temp_a3 << 0x10;
        M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF40000;
        M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
    }
jt_c1:
    M2C_FIELD(arg1, s32 *, 0x14) += 0x1C000;
    if (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6),
                      M2C_FIELD(arg1, s16 *, 0xA), temp_a3) < 0x200) {
        goto block_5;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
block_5:
    if (D_8008346A != 0) {
        goto block_20;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
jt_c2:
    temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x14);
    if (!(temp_v1_2 & 0x4000)) {
        goto block_10;
    }
    if (temp_v1_2 & 0x20000000) {
        goto block_10;
    }
    func_800ACF88(arg3);
block_10:
    func_800A56E0(0x805);
    M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
    M2C_FIELD(arg2, u16 *, 0x14) |= 0xC;
    M2C_FIELD(arg2, u16 *, 0x12) -= 0x80;
    M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
jt_c3:
    M2C_FIELD(arg1, s32 *, 0x14) += 0x1C000;
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x6000)) {
        goto block_20;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x80U;
    M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
    func_80173494();
    return;
jt_c4:
    M2C_FIELD(arg3, s32 *, 0x1C) |= 0x10000000;
    temp_v0 = (u8)M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg2, u8 *, 0xE) = temp_v0;
    M2C_FIELD(arg2, u8 *, 0xD) = temp_v0;
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 0x18;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((s16)temp_v0_2 >= 0x18) {
        goto block_20;
    }
    global_ptr = &D_80083460;
    if (M2C_FIELD(global_ptr, s32 *, 0x10) != (arg3 - 0x20)) {
        goto block_17;
    }
    M2C_FIELD(global_ptr, s32 *, 0x10) &= 0x7FFFFFFF;
block_17:
    func_800A2FE0(arg3, temp_a1, temp_a2, temp_a3);
    func_800A32A4(arg3);
    sound_x = M2C_FIELD(arg2, u8 *, 0x24);
    sound_y = M2C_FIELD(arg2, u8 *, 0x25);
    var_a2 = 0x3000;
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000)) {
        goto block_19;
    }
    var_a2 = 0x300;
block_19:
    func_8009A3D0(sound_x, sound_y, var_a2);
    func_8009A028(arg3);
    M2C_FIELD(arg3, u16 *, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
block_20:
    return;
}

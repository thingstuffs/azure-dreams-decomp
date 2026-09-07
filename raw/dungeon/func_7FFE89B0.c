#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_7003CF18();
s32 func_700750E0();
M2C_UNK func_7010B864();
extern s32 D_80086AD8;
extern u8 D_800E0F20[];
extern u16 D_80094422;
extern M2C_UNK D_8010B4EC;

void func_7FFE89B0(void *arg0, void *arg1, M2C_UNK arg2) {
    s32 var_s2;
    u16 temp_v0;
    u16 temp_v0_3;
    void *temp_a0;
    void *temp_s0;
    void *temp_v0_2;

    temp_a0 = M2C_FIELD(arg0, void **, 0x24);
    M2C_FIELD(arg1, s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), u16 *, 2) + M2C_FIELD(arg0, u16 *, 0x3C));
    M2C_FIELD(arg1, s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), u16 *, 6) + M2C_FIELD(arg0, u16 *, 0x3E));
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), u16 *, 0xA) + M2C_FIELD(arg0, u16 *, 0x40));
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x16) + 1;
    M2C_FIELD(arg0, u16 *, 0x16) = temp_v0;
    if ((s16) temp_v0 < 0x14) {
        var_s2 = 0;
        do {
            temp_v0_2 = func_7003CF18(0x212);
            var_s2 += 1;
            if (temp_v0_2 != NULL) {
                func_7010B864(temp_v0_2, arg0, arg1, arg2);
                M2C_FIELD(temp_v0_2, s16 *, 0x3E) = 0xA;
                M2C_FIELD(temp_v0_2, s16 *, 0x40) = 0xA;
                M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_8010B4EC;
                temp_s0 = M2C_FIELD(temp_v0_2, void **, 8);
                M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (((func_700750E0() & 0x7FFF) - 0x4000) << 7);
                M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (((func_700750E0() & 0x7FFF) - 0x4000) << 7);
                M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) (((func_700750E0() & 0x7FFF) - 0x4000) << 7);
                M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xA) - (D_800E0F20[M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0x13)] >> 1));
            }
        } while (var_s2 < 4);
    }
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x1E) - 1;
    M2C_FIELD(arg0, u16 *, 0x1E) = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        u16 *counter = &D_80094422;
        u16 next_counter;

        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        next_counter = *counter - 1;
        D_80086AD8 |= 0x8000;
        *counter = next_counter;
    }
}

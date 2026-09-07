#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

void *func_7003CF18();
M2C_UNK func_7010C7A8();
void *memcpy(void *, const void *, unsigned int);
extern s32 D_80086AD8;
extern u8 D_800E0F20[0x100];
extern u16 D_80094422;
extern M2C_UNK D_8010C460;
extern M2C_UNK D_8010C984;

void func_7FFEA1CC(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s16 temp_v1;
    u16 temp_v0_2;
    void *temp_a0;
    void *temp_v0;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u16 *, 0x16) + 1;
    M2C_FIELD(arg0, u16 *, 0x16) = (u16) temp_v1;
    if ((temp_v1 < 0x17) && (temp_v1 & 1)) {
        temp_v0 = func_7003CF18(0x212);
        if (temp_v0 != NULL) {
            func_7010C7A8(temp_v0, arg0, arg1, arg2);
            M2C_FIELD(temp_v0, s16 *, 0x3E) = 0x1E;
            M2C_FIELD(temp_v0, s16 *, 0x40) = 0x1E;
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8010C460;
            temp_a0 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_a0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_a0, u16 *, 0xA) - (D_800E0F20[M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0x13)] >> 1));
            temp_v1_2 = M2C_FIELD(temp_v0, void **, 0xC);
            memcpy((s8 *) temp_v0 + 0x62, &D_8010C984, 0xC);
            M2C_FIELD(temp_v1_2, void **, 8) = (void *) (temp_v0 + 0x62);
            M2C_FIELD(temp_v1_2, s16 *, 0x1E) = 0x32C8;
            M2C_FIELD(temp_v1_2, s16 *, 0x1C) = 0x32C8;
            M2C_FIELD(temp_v1_2, s16 *, 6) = 0x64;
            M2C_FIELD(temp_v1_2, s32 *, 0xC) = 0;
        }
    }
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x1E) - 1;
    M2C_FIELD(arg0, u16 *, 0x1E) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        u16 *counter = &D_80094422;
        u16 next_counter;

        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        next_counter = *counter - 1;
        D_80086AD8 |= 0x8000;
        *counter = next_counter;
    }
}

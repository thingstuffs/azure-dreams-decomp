#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s32 value;
    s32 pad[2];
} GlobalFlags;

M2C_UNK func_8004B248();
M2C_UNK func_800B15B8();
extern GlobalFlags D_800814A0;

void func_800B1664(void *arg0) {
    u16 temp_a0;
    s32 shifted;
    void *temp_a1;
    void *temp_v1;

    temp_a1 = M2C_FIELD(arg0, void **, 0xC0);
    temp_a0 = M2C_FIELD(temp_a1, u16 *, 6);
    shifted = temp_a0 << 0x10;
    M2C_FIELD(temp_a1, u16 *, 6) = (u16) (temp_a0 - ((s32) ((shifted >> 0x10) + ((u32) shifted >> 0x1F)) >> 1));
    temp_v1 = M2C_FIELD(arg0, void **, 0xC0);
    M2C_FIELD(temp_v1, u16 *, 4) = (u16) (M2C_FIELD(temp_v1, u16 *, 4) - 0x100);
    if ((s16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 6) < 0x11) {
        func_8004B248(arg0 + 0xD0, temp_a1);
        func_800B15B8(arg0);
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0.value |= 0x8000;
    }
}

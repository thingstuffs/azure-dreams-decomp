#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800478B8();
extern s32 D_800814A0[];

void func_800A86BC(void *arg0, void *arg1, void *arg2) {
    u8 temp;
    u16 count;

    M2C_FIELD(arg1, s32 *, 0x14) = M2C_FIELD(arg1, s32 *, 0x14) + M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(arg1, s32 *, 0) = M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 4) = M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 8) = M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14);
    func_800478B8(arg2);
    temp = M2C_FIELD(arg2, u8 *, 0xC);
    if (temp != 0) {
        temp -= 0x10;
        M2C_FIELD(arg2, u8 *, 0xC) = temp;
        M2C_FIELD(arg2, u8 *, 0xE) = temp;
        M2C_FIELD(arg2, u8 *, 0xD) = temp;
    }
    count = M2C_FIELD(arg0, u16 *, 2) - 1;
    M2C_FIELD(arg0, u16 *, 2) = count;
    if ((count << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = M2C_FIELD(arg0, u16 *, -2) | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}

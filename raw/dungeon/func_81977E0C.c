#include "common.h"
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_8002579C(void) __attribute__((noreturn));
extern void func_800478B8(void *);
s32 func_800644B8();
s32 func_80064584();
s32 rand();
extern s32 *D_80026208;
extern s32 D_800814A0;

void func_81977E0C(void *arg0, void *arg1, void *arg2) {
    u16 temp_a1;
    u16 temp_v0;
    u16 temp_v0_3;
    u8 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, u16 *, 4) + 1;
    M2C_FIELD(arg0, u16 *, 4) = temp_v0;
    if ((s16) temp_v0 >= 0xA) {
        temp_v0_2 = M2C_FIELD(arg2, u8 *, 0xE) - 0x10;
        M2C_FIELD(arg2, u8 *, 0xE) = temp_v0_2;
        M2C_FIELD(arg2, u8 *, 0xD) = temp_v0_2;
        M2C_FIELD(arg2, u8 *, 0xC) = temp_v0_2;
    }
    M2C_FIELD(arg0, u16 *, 8) = (u16) (M2C_FIELD(arg0, u16 *, 8) + 0x100);
    M2C_FIELD(arg0, u16 *, 6) = (u16) (M2C_FIELD(arg0, u16 *, 6) + 1);
    temp_a1 = (u16) (M2C_FIELD(arg0, u16 *, 0xA) - 8) - (rand() % 9);
    M2C_FIELD(arg0, u16 *, 0xA) = temp_a1;
    if ((u16) M2C_FIELD(arg2, u16 *, 0x1C) < 0x400U) {
        temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x40;
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_3;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_3;
    }
    func_800478B8(arg2);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
        func_8002579C();
        return;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) (*D_80026208 + (((func_800644B8((s16) M2C_FIELD(arg0, u16 *, 8)) >> 4) * (s16) M2C_FIELD(arg0, u16 *, 6)) << 8));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (D_80026208[1] + (((func_80064584((s16) M2C_FIELD(arg0, u16 *, 8)) >> 4) * (s16) M2C_FIELD(arg0, u16 *, 6)) << 8));
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(D_80026208, u16 *, 0xA) + M2C_FIELD(arg0, u16 *, 0xA));
}

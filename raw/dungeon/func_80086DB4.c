#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008C598() __attribute__((noreturn));
extern void func_800A56E0(u32);
extern s16 D_80083228[];
extern u8 D_800DD030[];

void func_8008C514(void *arg0, s32 arg1, void *arg2, void *arg3) {
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x1A;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x100000) {
        M2C_FIELD(arg2, u16 *, 0x14) |= 0x4000;
        func_8008C598(arg2);
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD030;
    func_80048A44(arg2, D_800DD030[((s32)(D_80083228[0] + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    func_800A56E0(0x50A);
    M2C_FIELD(arg0, s16 *, 0x96) = 0;
    M2C_FIELD(arg0, u16 *, 0xA2) = (u16)(M2C_FIELD(arg0, u16 *, 0xA2) & 0xFFEF);
}

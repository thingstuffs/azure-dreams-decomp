#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_80083120 {
    s16 field0;
    s16 field2;
    s16 field4;
    s16 field6;
} S_80083120;

extern u8 D_800DCFB0[8];
extern s16 D_80083228[5];
extern s16 D_800814E8;
extern S_80083120 D_80083120[8];

extern void func_80094E34(void);
extern s16 func_80042900(void *, s32);
extern void func_80048A44(void *, u8, s32, s32);
extern s16 func_800A4474(u8, u8);
extern s16 func_8003F794(s32, s32);
extern void func_800A9024(s32);

void func_8008D9F0(void *arg0, s32 arg1, void *arg2, void *arg3) {
    s16 temp_v0;
    s16 temp_v0_2;

    M2C_FIELD(arg0, s8 *, 0x9A) = 0x25;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    func_80094E34();
    if (func_80042900(arg3, 0xA) == 0) {
        M2C_FIELD(arg2, u8 **, 0x2C) = D_800DCFB0;
        func_80048A44(arg2, D_800DCFB0[((s32)(D_80083228[0] + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    }
    temp_v0 = func_800A4474(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    if (temp_v0 == 3) {
        temp_v0_2 = func_8003F794(6, 0x20);
        D_800814E8 = temp_v0_2;
        D_80083120[temp_v0_2].field6 = 1;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0x10;
        return;
    }
    if (temp_v0 == 4) {
        *(s32 *)0x80012090 = 2;
        func_800A9024(2);
    }
}

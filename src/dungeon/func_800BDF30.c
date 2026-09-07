#include "common.h"

extern void *D_800E3D7C;
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u8 D_800E17A1[];
extern u16 D_80083460[];

extern s32 func_8008D330();
extern void func_800C37B0(void);
extern void func_800A63B8();
extern s32 func_800AD6FC();
extern void func_800A5F38();
extern void func_800A56E0();
extern void func_80041E70();
extern void func_80099844();
extern void func_80098B38();

s32 func_800C3690(void *arg0, s32 arg1, s16 arg2)
{
    if (arg0 == D_800E3D7C) {
        *(s32 *)((u8 *)arg0 + 0x110) = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[*((u8 *)arg0 + 0x13)] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    }

    if (*((u8 *)arg0 + 0x26) >= 2) {
        func_800A56E0(0x615);
        (*((u8 *)arg0 + 0x26))--;
        func_80041E70(arg0);
        if (*(s32 *)((u8 *)arg0 + 0x14) & 0x4000) {
            func_80099844(arg0, D_800E17A1);
        }
    }

    func_80098B38(arg1);
    D_80083460[5]--;
    return 1;
}

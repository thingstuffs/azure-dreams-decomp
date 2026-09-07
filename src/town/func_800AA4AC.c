#include "common.h"

extern s32 func_8009CFE0(void);
extern void func_800A7C5C(void);
extern void func_80033D08(void *arg0);

extern int D_800814A0;

void func_800A7C0C(void *arg0)
{
    void *p;
    u16 temp;

    if (func_8009CFE0() != 0) {
        p = *(void **)((u8 *)arg0 + 0x98);
        if (p != 0) {
            *(u8 *)p = 0;
            func_800A7C5C();
            return;
        }
    } else {
        temp = *(u16 *)((u8 *)arg0 + 0x6C) - 1;
        *(u16 *)((u8 *)arg0 + 0x6C) = temp;
        if ((s16)temp > 0) {
            return;
        }
    }

    func_80033D08(arg0);
    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
    D_800814A0 |= 0x8000;
}

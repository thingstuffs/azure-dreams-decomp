#include "common.h"

extern s32 func_8009CFE0(void *, void *);
extern void func_80033D08(void *arg0);
extern s32 D_800814A0[3];

void func_800B9CB8(void *arg0, void *arg1)
{
    u8 *byte;

    if (func_8009CFE0(arg0, arg1) != 0) {
        byte = *(u8 **)((u8 *)arg0 + 0x98);
        if (byte != 0) {
            *byte = 0;
        }
        func_80033D08(arg0);
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    *(u16 *)((u8 *)arg0 + 0x66) =
        *(u16 *)((u8 *)arg0 + 0x66) + *(s8 *)((u8 *)arg0 + 0x97);
    *(s16 *)((u8 *)arg0 + 0x66) %= 0x1000;
}

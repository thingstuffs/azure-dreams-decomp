#include "common.h"

typedef void (*Callback)(void *, s32, s32);

extern u32 func_8009CFE0(void *, s32);
extern void func_8008F134(void *);
extern void func_80033D08(void *);
extern s32 D_800814A0[];

void func_800C25C0(void *arg0, s32 arg1, s32 arg2) {
    u16 *flags;
    s8 *byte;

    if (func_8009CFE0(arg0, arg1) != 0) {
        func_8008F134(arg0);
        byte = *(s8 **)((u8 *)arg0 + 0x98);
        if (byte != 0) {
            *byte = 0;
        }
        func_80033D08(arg0);
        flags = (u16 *)arg0 - 1;
        *flags |= 0x8000;
        D_800814A0[0] |= 0x8000;
    } else {
        (*(Callback *)((u8 *)arg0 + 0x50))(arg0, arg1, arg2);
    }
}

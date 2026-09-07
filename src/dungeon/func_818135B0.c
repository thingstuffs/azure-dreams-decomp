#include "common.h"

extern void func_80028534(void *arg0);
extern void func_8004B1A4(void *arg0);
extern void func_8004B248(void *arg0);
extern s32 D_800814A0[3];

void func_800285B0(void *arg0)
{
    u8 *sub;
    u16 field;
    s32 flags;

    if (arg0 != 0) {
        sub = (u8 *)arg0 + 0x20;
        func_80028534(*(void **)(sub + 0x88));
        func_8004B1A4(*(void **)(sub + 0x40));
        func_8004B248((u8 *)arg0 + 0xAC);
        field = *(u16 *)((u8 *)arg0 + 0x1E);
        flags = D_800814A0[0];
        *(u16 *)((u8 *)arg0 + 0x1E) = field | 0x8000;
        D_800814A0[0] = flags | 0x8000;
    }
}

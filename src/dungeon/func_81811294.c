#include "common.h"

extern void func_80026250(void *arg0);
extern void func_8004B248(u16 **arg0);
extern s32 D_800814A0[3];

void func_80026294(void *arg0)
{
    u16 field;
    s32 flags;

    if (arg0 != 0) {
        func_80026250(*(void **)((u8 *)arg0 + 0x74));
        func_8004B248((u16 **)((u8 *)arg0 + 0x78));
        field = *(u16 *)((u8 *)arg0 + 0x1E);
        flags = D_800814A0[0];
        *(u16 *)((u8 *)arg0 + 0x1E) = field | 0x8000;
        D_800814A0[0] = flags | 0x8000;
    }
}

#include "common.h"

extern void func_8004B1A4(s32 arg0);
extern s32 D_800E5910[];
extern s32 D_800814A0[3];

void func_800DCE0C(void *arg0)
{
    func_8004B1A4(*(s32 *)((u8 *)arg0 + 0x5C));
    D_800E5910[0] = 0;
    {
        u16 field = *(u16 *)((u8 *)arg0 + 0x1E);
        s32 flags = D_800814A0[0];
        *(u16 *)((u8 *)arg0 + 0x1E) = field | 0x8000;
        D_800814A0[0] = flags | 0x8000;
    }
}

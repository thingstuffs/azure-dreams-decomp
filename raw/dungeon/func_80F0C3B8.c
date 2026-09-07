#include "common.h"

extern void func_80044A50(void *);
extern void func_800BC318(void *);
extern void func_800AD594(void *, s32);

extern s16 D_80083460[];
extern u8 D_80170F74[];

void func_80173BB8(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    u8 value;
    void *ptr;

    if (*(u8 *)((u8 *)arg0 + 0x9B) == 0) {
        value = *(u8 *)((u8 *)arg2 + 0xC) - 0x10;
        *(u8 *)((u8 *)arg2 + 0xE) = value;
        *(u8 *)((u8 *)arg2 + 0xD) = value;
        *(u8 *)((u8 *)arg2 + 0xC) = value;
        if (*(u16 *)((u8 *)arg2 + 0x14) & 0xE000) {
            ptr = (u8 *)arg0 - 0x20;
            func_80044A50(ptr);
            func_800BC318(ptr);
            func_800AD594(arg3, 0x800);
            D_80083460[5]--;
            *(u32 *)((u8 *)arg2 + 0xC) = 0;
            *(u8 *)((u8 *)arg3 + 0x6D) = 0;
            *(u16 *)((u8 *)arg3 + 0x46) &= 0x7FFF;
            *(void **)((u8 *)arg0 + 0x8C) = D_80170F74;
        }
    }
}

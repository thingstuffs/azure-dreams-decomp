#include "common.h"

extern u32 func_800478B8();
extern s32 D_800814A0[];

void func_81868F30(void *arg0, void *arg1, void *arg2) {
    u16 value;
    u8 byte;
    void *ptr;

    ptr = *(void **)arg0;
    *(u16 *)((u8 *)ptr + 0x14) = *(u16 *)((u8 *)ptr + 0x14) + 1;
    value = *(u16 *)((u8 *)arg2 + 0x1E) - 0x400;
    byte = *(u8 *)((u8 *)arg2 + 0xE) + 4;
    *(u16 *)((u8 *)arg2 + 0x1E) = value;
    *(u16 *)((u8 *)arg2 + 0x1C) = value;
    *(u8 *)((u8 *)arg2 + 0xE) = byte;
    *(u8 *)((u8 *)arg2 + 0xD) = byte;
    *(u8 *)((u8 *)arg2 + 0xC) = byte;
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(s8 *)((u8 *)*(void **)arg0 + 0x16) = 1;
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

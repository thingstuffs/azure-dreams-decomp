#include "common.h"

typedef s32 M2C_UNK;

extern s8 func_800374F4();
extern M2C_UNK func_8009B454();
extern M2C_UNK func_8009BFD8();

void func_800AAC64(void *arg0, M2C_UNK arg1, M2C_UNK arg2, void *arg3) {
    s32 temp_s2;
    s16 temp_v0;

    *(s8 *)((s8 *)arg3 + 0xC) = func_800374F4(0x100);
    *(s8 *)((s8 *)arg3 + 0xD) = func_800374F4(0x100);
    *(s8 *)((s8 *)arg3 + 0xE) = func_800374F4(0x100);
    temp_s2 = *(s32 *)((s8 *)arg0 + 0x50);
    func_8009B454(arg0, arg1, arg2, arg3);
    temp_v0 = *(u16 *)((s8 *)arg0 + 0x6C) - 1;
    *(u16 *)((s8 *)arg0 + 0x6C) = temp_v0;
    if ((temp_v0 < 0) || (*(s32 *)((s8 *)arg0 + 0x50) != temp_s2)) {
        func_8009BFD8(arg0, arg1, arg2, arg3);
        *(u8 *)((u8 *)arg3 + 0xC) = 0x80;
        *(u8 *)((u8 *)arg3 + 0xD) = 0x80;
        *(u8 *)((u8 *)arg3 + 0xE) = 0x80;
    }
}

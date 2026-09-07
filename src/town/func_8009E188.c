#include "common.h"

extern s32 D_80083780[];

extern void func_8009539C(void *arg0);
extern void func_8008F294(void *arg0, void *arg1);
extern void func_8008F664(void *arg0, void *arg1);
extern void func_8009C1B4(void *arg0, s32 arg1, void *arg2, s32 arg3);

void func_8009B8E8(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    u16 temp_v0;

    *(s32 *)((u8 *)arg2 + 0xC) = (D_80083780[0] - *(s32 *)arg2) / 2;
    *(s32 *)((u8 *)arg2 + 0x10) = (D_80083780[1] - *(s32 *)((u8 *)arg2 + 4)) / 2;
    func_8009539C(arg2);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    temp_v0 = *(u16 *)((u8 *)arg0 + 0x6C) - 1;
    *(u16 *)((u8 *)arg0 + 0x6C) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_8009C1B4(arg0, arg1, arg2, arg3);
    }
}

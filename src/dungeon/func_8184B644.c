#include "common.h"

extern s32 func_80024930();

s32 func_80024E44(void *arg0, s32 arg1, s32 arg2) {
    s32 size = 0x140;
    u16 value;

    value = *(u16 *)((u8 *)arg0 + 0x14);
    func_80024930(arg0, arg1, arg2, (s16)(value << 5), size, 0x20, 3, 0x40);

    value = *(u16 *)((u8 *)arg0 + 0x14);
    func_80024930(arg0, arg1, arg2, (s16)-(value << 6), size, 0x18, 1, 0xFF);

    return 0;
}

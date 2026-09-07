#include "common.h"

void func_80023A50(s32 arg0, s32 arg1) {
    s32 *v0;

    if (arg0 != 0) {
        v0 = (s32 *)(arg0 + 0x20);
        arg0 = *(s32 *)((u8 *)v0 + 0x88);
        *(s32 *)((u8 *)v0 + 0x84) = 0;
        *(s32 *)((u8 *)v0 + 0x80) = 3;
        *(s32 *)((u8 *)v0 + 0x88) = arg1;
        *(s32 *)((u8 *)v0 + 0x8C) = arg0;
    }
}

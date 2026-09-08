#include "common.h"

extern s32 D_800814A0[];

void func_800DB618(void *arg0) {
    s32 current = *(s32 *)((s8 *)arg0 + 0x18);
    s32 limit = *(s32 *)((s8 *)arg0 + 0x1C);

    if (current >= limit) {
        *(s32 *)((s8 *)arg0 + 0x18) = current - limit;
        return;
    }
    *(u16 *)((s8 *)arg0 - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}

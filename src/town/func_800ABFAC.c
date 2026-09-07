#include "common.h"

void func_800A970C(s32 unused, void *arg1) {
    *(u16 *)((u8 *)arg1 + 0xE) += 0x20;
    *(u16 *)((u8 *)arg1 + 0x12) += 0x4E;
    *(u16 *)((u8 *)arg1 + 0x16) -= 0x1E;
}

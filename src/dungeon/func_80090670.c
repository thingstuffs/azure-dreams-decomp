#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 unk0C;
    u8 pad1[0x14 - 0x10];
    u16 unk14;
} D_80083460_t;

extern D_80083460_t D_80083460;

void func_80095DD0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    *((u8 *)arg0 + 0x9A) = 0x15;
    *((u8 *)arg0 + 0x9B) = 0;
    *(s32 *)((u8 *)arg0 + 0x8C) = 0;
    D_80083460.unk0C = arg3;
    D_80083460.unk14++;
}

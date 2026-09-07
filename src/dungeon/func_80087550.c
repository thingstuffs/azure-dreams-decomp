#include "common.h"

typedef struct {
    u16 unk0;
    u16 flags;
    s32 unk4;
    s32 unk8;
} Status;

extern void func_80048A44(void *, u8, s32, s32);
extern s16 D_80083228;
extern Status D_80083460;
extern u8 D_800DD000[];

void func_8008CCB0(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 value = 0x17;

    if (*(u8 *)((s8 *)arg0 + 0x9A) != value) {
        *(u8 **)((s8 *)arg2 + 0x2C) = D_800DD000;
        func_80048A44(arg2, D_800DD000[((D_80083228 + *(s16 *)((s8 *)arg3 + 0x2A) + 0x100) >> 9) & 7], 0, 1);
        D_80083460.flags |= 0x100;
        *(u8 *)((s8 *)arg0 + 0x9A) = value;
        *(s8 *)((s8 *)arg0 + 0x9B) = 0;
        *(s32 *)((s8 *)arg0 + 0x8C) = 0;
    }
}

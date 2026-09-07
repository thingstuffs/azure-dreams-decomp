#include "common.h"

typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[6];
    u16 count;
} DungeonState;

extern DungeonState D_80083460;
extern void func_800AA878(void);
extern void func_800ACB98(void *, s32, void *, void *);

s32 func_800AA79C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    DungeonState *state = &D_80083460;

    *(u8 *)((u8 *)arg3 + 0x71) &= 0x7F;
    if (state->flags & 0x2008) {
        *(volatile s8 *)((u8 *)arg0 + 0x9A) = 0xE;
        return 0;
    }
    if (*(s32 *)((u8 *)arg3 + 0x14) & 0x20000000) {
        func_800ACB98(arg0, arg1, arg2, arg3);
        return 1;
    }
    if (!(*(s32 *)((u8 *)arg3 + 0x1C) & 8)) {
        state->count--;
    }
    *(s8 *)((u8 *)arg0 + 0x9A) = 5;
    *(s8 *)((u8 *)arg0 + 0x9B) = 0;
    *(s32 *)((u8 *)arg0 + 0x8C) = 0;
    *(u16 *)((u8 *)arg0 + 0x98) &= 0xFFF7;
    *(s16 *)((u8 *)arg3 + 0x24) = 0;
    state->count++;
    *(s32 *)((u8 *)arg3 + 0x1C) =
        (*(s32 *)((u8 *)arg3 + 0x1C) | 8) & 0xFFFBFFFF;
    *(u16 *)((u8 *)arg2 + 0x14) |= 0x6000;
    return 1;
}

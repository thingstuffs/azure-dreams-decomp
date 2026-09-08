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

/* Enters state 0x17, selects its directional animation, and resets state progress. */
void func_8008CCB0(void *state, void *unused, void *animation, void *orientation) {
    u8 next_state = 0x17;

    if (*(u8 *)((s8 *)state + 0x9A) != next_state) {
        *(u8 **)((s8 *)animation + 0x2C) = D_800DD000;
        func_80048A44(animation, D_800DD000[((D_80083228 + *(s16 *)((s8 *)orientation + 0x2A) + 0x100) >> 9) & 7], 0, 1);
        D_80083460.flags |= 0x100;
        *(u8 *)((s8 *)state + 0x9A) = next_state;
        *(s8 *)((s8 *)state + 0x9B) = 0;
        *(s32 *)((s8 *)state + 0x8C) = 0;
    }
}

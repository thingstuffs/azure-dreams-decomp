#include "common.h"

extern s32 func_800AC82C(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);

extern s16 D_80083228;
extern u8 D_80164F20[];
extern u8 D_80167B98[];
extern u8 D_8016A2C8[];
extern u8 D_8016A300[];
extern u8 D_8016A328[];
extern u8 D_8016A360[];

/* Updates object state or switches the sprite table and selects a directional frame. */
void func_80167720(void *state_arg, void *context, void *sprite_arg, void *actor_arg) {
    void *state = state_arg;
    void *sprite = sprite_arg;
    void *actor = actor_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *active_table;

    if (func_800AC82C(state_arg, context, sprite_arg, actor_arg) != 0) {
        if ((func_800AD9B4(sprite, actor) << 0x10) > 0) {
            if (*(u8 *)((u8 *)state + 0xA7) != 0) {
                *(void **)((u8 *)state + 0x8C) = D_80167B98;
            } else {
                *(void **)((u8 *)state + 0x8C) = D_80164F20;
            }
        }
        return;
    }

    active_table = *(void **)((u8 *)sprite + 0x2C);
    if (active_table == D_8016A300) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)sprite + 0x2C) = D_8016A2C8;
        func_80047784(sprite, D_8016A2C8[((D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7], 0);
    } else if (active_table == D_8016A360) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)sprite + 0x2C) = D_8016A328;
        func_80047784(sprite, D_8016A328[((D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7], 0);
    } else {
        return;
    }

}

/* MECHANISM: The 0x20 frame and s1/s0/s2 held arguments preserve the proven CFG.
   Pinned a0 call-object and v0 frame_entry lifetimes fill the lh delay slot without length drift.
   Integer direction-first address addition defeats pointer-first canonicalization at word 57. */

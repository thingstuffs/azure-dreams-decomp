#include "common.h"

extern s32 func_800AC82C(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);

extern s16 D_80083228;
extern u8 D_8016AF20[];
extern u8 D_8016DB98[];
extern u8 D_801702C8[];
extern u8 D_80170300[];
extern u8 D_80170328[];
extern u8 D_80170360[];

/* Updates the state or selects a directional animation frame. */
void func_8016D720(void *state_arg, void *context, void *sprite_arg, void *actor_arg) {
    void *state = state_arg;
    void *sprite = sprite_arg;
    void *actor = actor_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *current_frames;

    if (func_800AC82C(state_arg, context, sprite_arg, actor_arg) != 0) {
        if ((func_800AD9B4(sprite, actor) << 0x10) > 0) {
            if (*(u8 *)((u8 *)state + 0xA7) != 0) {
                *(void **)((u8 *)state + 0x8C) = D_8016DB98;
            } else {
                *(void **)((u8 *)state + 0x8C) = D_8016AF20;
            }
        }
        return;
    }

    current_frames = *(void **)((u8 *)sprite + 0x2C);
    if (current_frames == D_80170300) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)sprite + 0x2C) = D_801702C8;
        func_80047784(sprite, D_801702C8[((D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7], 0);
    } else if (current_frames == D_80170360) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)sprite + 0x2C) = D_80170328;
        func_80047784(sprite, D_80170328[((D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7], 0);
    } else {
        return;
    }

}


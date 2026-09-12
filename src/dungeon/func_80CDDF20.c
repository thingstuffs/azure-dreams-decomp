#include "common.h"

extern s32 func_800AC82C(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);

extern s16 D_80083228;
extern u8 D_80152F20[];
extern u8 D_80155B98[];
extern u8 D_801582C8[];
extern u8 D_80158300[];
extern u8 D_80158328[];
extern u8 D_80158360[];

/* Updates the owner's animation or selects a sprite frame for the actor's direction. */
void func_80155720(void *owner_arg, void *context, void *sprite_arg, void *actor_arg) {
    void *owner = owner_arg;
    void *sprite = sprite_arg;
    void *actor = actor_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *frame_set;

    if (func_800AC82C(owner_arg, context, sprite_arg, actor_arg) != 0) {
        if ((func_800AD9B4(sprite, actor) << 0x10) > 0) {
            if (*(u8 *)((u8 *)owner + 0xA7) != 0) {
                *(void **)((u8 *)owner + 0x8C) = D_80155B98;
            } else {
                *(void **)((u8 *)owner + 0x8C) = D_80152F20;
            }
        }
        return;
    }

    frame_set = *(void **)((u8 *)sprite + 0x2C);
    if (frame_set == D_80158300) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)sprite + 0x2C) = D_801582C8;
        func_80047784(sprite, D_801582C8[((D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7], 0);
    } else if (frame_set == D_80158360) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)sprite + 0x2C) = D_80158328;
        func_80047784(sprite, D_80158328[((D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7], 0);
    } else {
        return;
    }

}


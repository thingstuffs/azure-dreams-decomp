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
    register void *actor ASM_REG("$18") = actor_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *current_frames;
    register u8 *direction_frames ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *frame_entry;
    void *frame_sprite;
    s32 direction;

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
        direction_frames = D_801702C8;
    } else if (current_frames == D_80170360) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        direction_frames = D_80170328;
    } else {
        return;
    }

    *(void **)((u8 *)sprite + 0x2C) = direction_frames;
    direction = (D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9;
    frame_sprite = sprite;
    frame_entry = (u8 *)((u32)(direction & 7) + (u32)direction_frames);
    func_80047784(frame_sprite, *frame_entry, 0);
}


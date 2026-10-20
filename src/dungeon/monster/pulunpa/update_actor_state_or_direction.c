#include "common.h"
#include "shared/game_work.h"

extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);
extern s32 check_actor_floor_trap(void *, void *);
extern void select_sprite_entry(void *, u8, s32);

extern u8 D_8016AF20[];
extern u8 D_8016DB98[];
extern u8 D_801702C8[];
extern u8 D_80170300[];
extern u8 D_80170328[];
extern u8 D_80170360[];

/* Updates the state or selects a directional animation frame. */
void update_actor_state_or_direction(void *state_arg, void *context, void *sprite_arg, void *actor_arg) {
    void *state = state_arg;
    void *sprite = sprite_arg;
    void *actor = actor_arg;
    void *current_frames;

    if (update_actor_transform_from_parent(state_arg, context, sprite_arg, actor_arg) != 0) {
        if ((check_actor_floor_trap(sprite, actor) << 0x10) > 0) {
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
        select_sprite_entry(sprite, D_801702C8[((g_game_work.view.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else if (current_frames == D_80170360) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)sprite + 0x2C) = D_80170328;
        select_sprite_entry(sprite, D_80170328[((g_game_work.view.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else {
        return;
    }

}


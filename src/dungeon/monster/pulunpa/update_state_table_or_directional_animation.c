#include "common.h"
#include "shared/game_work.h"

extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);
extern s32 check_actor_floor_trap(void *, void *);
extern void select_sprite_entry(void *, u8, s32);

extern u8 D_8014CF20[];
extern u8 D_8014FB98[];
extern u8 D_801522C8[];
extern u8 D_80152300[];
extern u8 D_80152328[];
extern u8 D_80152360[];

/* Updates the state table or selects a directional animation for the actor. */
void update_state_table_or_directional_animation(void *state_arg, void *context, void *visual_arg, void *actor_arg) {
    void *state = state_arg;
    void *visual = visual_arg;
    void *actor = actor_arg;
    void *current_table;

    if (update_actor_transform_from_parent(state_arg, context, visual_arg, actor_arg) != 0) {
        if ((check_actor_floor_trap(visual, actor) << 0x10) > 0) {
            if (*(u8 *)((u8 *)state + 0xA7) != 0) {
                *(void **)((u8 *)state + 0x8C) = D_8014FB98;
            } else {
                *(void **)((u8 *)state + 0x8C) = D_8014CF20;
            }
        }
        return;
    }

    current_table = *(void **)((u8 *)visual + 0x2C);
    if (current_table == D_80152300) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)visual + 0x2C) = D_801522C8;
        select_sprite_entry(visual, D_801522C8[((g_game_work.view.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else if (current_table == D_80152360) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)visual + 0x2C) = D_80152328;
        select_sprite_entry(visual, D_80152328[((g_game_work.view.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else {
        return;
    }

}

/* MECHANISM: The 0x20 frame and s1/s0/s2 held arguments preserve the proven CFG. Integer direction-
   first address addition defeats pointer-first canonicalization at word 57. */

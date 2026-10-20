#include "common.h"
#include "shared/game_work.h"

extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);
extern s32 check_actor_floor_trap(void *, void *);
extern void select_sprite_entry(void *, u8, s32);

extern u8 D_80164F20[];
extern u8 D_80167B98[];
extern u8 D_8016A2C8[];
extern u8 D_8016A300[];
extern u8 D_8016A328[];
extern u8 D_8016A360[];

/* Updates object state or switches the sprite table and selects a directional frame. */
void update_object_state_or_directional_sprite(void *state_arg, void *context, void *sprite_arg, void *actor_arg) {
    void *state = state_arg;
    void *sprite = sprite_arg;
    void *actor = actor_arg;
    void *active_table;

    if (update_actor_transform_from_parent(state_arg, context, sprite_arg, actor_arg) != 0) {
        if ((check_actor_floor_trap(sprite, actor) << 0x10) > 0) {
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
        select_sprite_entry(sprite, D_8016A2C8[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else if (active_table == D_8016A360) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)sprite + 0x2C) = D_8016A328;
        select_sprite_entry(sprite, D_8016A328[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else {
        return;
    }

}

/* MECHANISM: The 0x20 frame and s1/s0/s2 held arguments preserve the proven CFG. Integer direction-
   first address addition defeats pointer-first canonicalization at word 57. */

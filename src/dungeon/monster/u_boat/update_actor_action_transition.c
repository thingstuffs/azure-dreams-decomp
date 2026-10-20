#include "common.h"
#include "shared/game_work.h"

extern s32 update_actor_transform_from_parent(void *, s32, void *, void *);
extern s32 check_actor_floor_trap(void *, void *);
extern void select_sprite_entry(void *, u8, s32);
extern void create_owner_linked_directional_object(void *, s32, void *);

extern u8 D_800E23E0[];
extern u8 D_800E2428[];
extern u8 D_80171A80[];

/* Selects a response state or updates the sprite's directional animation. */
void update_actor_action_transition(void *state, s32 update_mode, void *sprite, void *entity)
{
    if (update_actor_transform_from_parent(state, update_mode, sprite, entity) != 0) {
        if ((check_actor_floor_trap(sprite, entity) << 16) > 0) {
            *(void **)((u8 *)state + 0x8C) = D_80171A80;
            return;
        }
    } else if (*(void **)((u8 *)sprite + 0x2C) == D_800E2428 &&
               !(*(s32 *)((u8 *)entity + 0x1C) & 0x208)) {
        u8 *direction_frames;

        direction_frames = D_800E23E0;
        *(void **)((u8 *)sprite + 0x2C) = direction_frames;
        select_sprite_entry(
            sprite,
            direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)entity + 0x2A) + 0x100) >> 9) & 7],
            0);
        if (*(u8 *)((u8 *)state + 0xB0) == 0) {
            create_owner_linked_directional_object(state, update_mode, sprite);
        }
    }
}

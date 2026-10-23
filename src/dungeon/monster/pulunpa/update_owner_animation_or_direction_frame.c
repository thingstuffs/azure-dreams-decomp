#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);

extern void select_sprite_entry(void *, u8, s32);

extern u8 D_80152F20[];
extern u8 D_80155B98[];
extern u8 D_801582C8[];
extern u8 D_80158300[];
extern u8 D_80158328[];
extern u8 D_80158360[];

/* Updates the owner's animation or selects a sprite frame for the actor's direction. */
void update_owner_animation_or_direction_frame(void *owner_arg, void *context, void *sprite_arg, void *actor_arg) {
    void *owner = owner_arg;
    SpriteFrameState *sprite= sprite_arg;
    void *actor = actor_arg;
    void *frame_set;

    if (update_actor_transform_from_parent(owner_arg, context, sprite_arg, actor_arg) != 0) {
        if ((check_actor_floor_trap(sprite, actor) << 0x10) > 0) {
            if (*(u8 *)((u8 *)owner + 0xA7) != 0) {
                *(void **)((u8 *)owner + 0x8C) = D_80155B98;
            } else {
                *(void **)((u8 *)owner + 0x8C) = D_80152F20;
            }
        }
        return;
    }

    frame_set = sprite->frameTable;
    if (frame_set == D_80158300) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        sprite->frameTable = D_801582C8;
        select_sprite_entry(sprite, D_801582C8[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else if (frame_set == D_80158360) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        sprite->frameTable = D_80158328;
        select_sprite_entry(sprite, D_80158328[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else {
        return;
    }

}


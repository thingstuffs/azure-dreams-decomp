#include "shared/entity.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "engine/graphics.h"

extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);

extern u8 uboat_default_frames[];
extern u8 uboat_action_frames[];
#include "dungeon/monster/u_boat.h"

/* Selects a response state or updates the sprite's directional animation. */
void update_actor_action_transition(ActorRecord *state, ObjectPosition *update_mode, SpriteFrameState *sprite, ActorRecord *entity)
{
    if (update_actor_transform_from_parent(state, update_mode, sprite, entity) != 0) {
        if ((check_actor_floor_trap(sprite, entity) << 16) > 0) {
            state->unk_8C.address = uboat_behavior_entry;
            return;
        }
    } else if (sprite->frameTable == uboat_action_frames &&
               !(entity->flags1C & 0x208)) {
        u8 *direction_frames;

        direction_frames = uboat_default_frames;
        sprite->frameTable = direction_frames;
        select_sprite_entry(
            sprite,
            direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        if (state->unk_B0.bytes[0] == 0) {
            create_owner_linked_directional_object(state, update_mode, sprite);
        }
    }
}

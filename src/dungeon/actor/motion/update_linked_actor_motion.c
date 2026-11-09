#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor/motion.h"
#include "dungeon/player/object.h"

/* Follows the linked position until the countdown expires, then resets and marks completion. */
s32 update_linked_actor_motion(void *state_data, ObjectPosition *transform, SpriteFrameState *config, ActorRecord *object) {
    ActorRecord *state = state_data;

    s16 ticks_left;
    void *linked_transform;

    if (config->flags & 0x8000) {
        state->action_timer = 0;
    }
    if (state->action_timer != 0) {
        linked_transform = *(void **)((u8 *)object->target - 0x18);
        transform->velocity_x = *(s32 *)((u8 *)linked_transform + 0xC);
        transform->velocity_y = *(s32 *)((u8 *)linked_transform + 0x10);
    }
    ticks_left = state->action_timer - 1;
    state->action_timer = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        return 0;
    }
    transform->velocity_z = 0;
    transform->velocity_y = 0;
    transform->velocity_x = 0;
    set_record_integer_tile_center(transform, config->tile_x, config->tile_y);
    state->action_state_flags &= 0xFFF7;
    object->flags1C |= 0x40000000;
    g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
    return 1;
}

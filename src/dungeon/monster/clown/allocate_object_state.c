#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "dungeon/monster/clown/allocate_object_state.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/clown/allocate_object_state.h"

/* Creates a Clown actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *allocate_object_state_and_callbacks(s16 init_flags, s16 grid_x, s16 grid_y, s16 type_id)
{
    s32 mode;
    s32 state_flags;
    s32 update_flags;
    SpriteFrameState *placement;
    ObjectPosition *config;
    ObjectNodeHeader *object;
    S_8014C878_4 *extended_state;
    S_8014C878_1 *state;
    s8 saved_x;
    register s16 saved_type;
    s8 saved_y;

    state = 0;
    saved_x = grid_x;
    saved_type = type_id;
    saved_y = grid_y;
    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        state = 
        ((void *)object)+ 0x20;
        object->update_callback = &clown_object_callback;
        state->unk_13 = MONSTER_CLOWN;
        register_node(object, project_sprite_chain);
        config = object->position;
        config->z.w.i = saved_type;
        placement = object->sprite;
        mode = init_flags & 3;
        placement->tile_y = saved_y;
        extended_state = state;
        placement->frameTable = &D_8015020C;
        placement->tile_x = saved_x;
        if (mode == 1) {
            state_flags = state->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            update_flags = state->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            state->unk_14 = state_flags;
            state->unk_1C = update_flags;
        } else if (mode >= 2) {
            state_flags = state->unk_14 | ACTOR_CLASS_ENABLED;
            update_flags = state->unk_1C | ACTOR_PLAYER_SIDE;
            state->unk_14 = state_flags;
            state->unk_1C = update_flags;
        } else if (((init_flags & ~3) << 0x10) == 0) {
            if (!(state->unk_14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    set_or_clear_actor_status_slot(state, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    placement->frameTable = &D_8015025C;
                }
            }
        }
        initialize_actor_sprite_and_animation(object, config, placement, init_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &D_8014D014;
        state->unk_1C = (s32)(state->unk_1C | 0x40000);
        extended_state->unk_92 = -0x20;
        try_move_actor_to_valid_position(extended_state, config, placement, state);
    }
    return state;
}

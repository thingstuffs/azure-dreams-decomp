#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "modules/dungeon_ovl_7f535800.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"

/* Creates a Clown actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_clown_slot_c(s16 init_flags, s16 pos_x, s16 pos_y, s16 init_value)
{
    s32 init_mode;
    s32 state_flags;
    s32 update_flags;
    SpriteFrameState *placement_data;
    ObjectPosition *config_data;
    ObjectNodeHeader *object;
    S_80158878_4 *extended_state;
    S_80158878_1 *state;
    s8 saved_x;
    register s16 saved_value;
    s8 saved_y;

    state = 0;
    saved_x = pos_x;
    saved_value = init_value;
    saved_y = pos_y;
    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        state = 
        ((void *)object)+ 0x20;
        object->update_callback = &clown_object_callback_2;
        state->unk_13 = MONSTER_CLOWN;
        register_node(object, project_sprite_chain);
        config_data = object->position;
        config_data->z.w.i = saved_value;
        placement_data = object->sprite;
        init_mode = init_flags & 3;
        placement_data->tile_y = saved_y;
        extended_state = state;
        placement_data->frameTable = &D_8015C20C;
        placement_data->tile_x = saved_x;
        if (init_mode == 1) {
            state_flags = state->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            update_flags = state->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            state->unk_14 = state_flags;
            state->unk_1C = update_flags;
        } else if (init_mode >= 2) {
            state_flags = state->unk_14 | ACTOR_CLASS_ENABLED;
            update_flags = state->unk_1C | ACTOR_PLAYER_SIDE;
            state->unk_14 = state_flags;
            state->unk_1C = update_flags;
        } else if (((init_flags & ~3) << 0x10) == 0) {
            if (!(state->unk_14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    set_or_clear_actor_status_slot(state, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    placement_data->frameTable = &D_8015C25C;
                }
            }
        }
        initialize_actor_sprite_and_animation(object, config_data, placement_data, init_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &D_80159014;
        state->unk_1C = (s32)(state->unk_1C | 0x40000);
        extended_state->unk_92 = -0x20;
        try_move_actor_to_valid_position(extended_state, config_data, placement_data, state);
    }
    return state;
}

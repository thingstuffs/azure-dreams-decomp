#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "dungeon/monster/clown/create_flagged_actor_object.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"

/* Creates a Clown actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_flagged_actor_object(s16 init_flags, s16 tile_x, s16 tile_y, s16 object_id)
{
    s32 mode;
    s32 flags_14;
    s32 flags_1c;
    SpriteFrameState *placement;
    SignedHeightView *object_data;
    ObjectNodeHeader *object;
    S_8016A878_4 *runtime;
    S_8016A878_1 *state;
    s8 saved_x;
    register s16 saved_id;
    s8 saved_y;

    state = 0;
    saved_x = tile_x;
    saved_id = object_id;
    saved_y = tile_y;
    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        state = 
        ((void *)object)+ 0x20;
        object->update_callback = clown_object_callback_4;
        state->unk_13 = MONSTER_CLOWN;
        register_node(object, project_sprite_chain);
        object_data = object->position;
        object_data->z = saved_id;
        placement = object->sprite;
        mode = init_flags & 3;
        placement->tile_y = saved_y;
        runtime = state;
        placement->frameTable = &D_8016E20C;
        placement->tile_x = saved_x;
        if (mode == 1) {
            flags_14 = state->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags_1c = state->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            state->unk_14 = flags_14;
            state->unk_1C = flags_1c;
        } else if (mode >= 2) {
            flags_14 = state->unk_14 | ACTOR_CLASS_ENABLED;
            flags_1c = state->unk_1C | ACTOR_PLAYER_SIDE;
            state->unk_14 = flags_14;
            state->unk_1C = flags_1c;
        } else if (((init_flags & ~3) << 0x10) == 0) {
            if (!(state->unk_14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    set_or_clear_actor_status_slot(state, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    placement->frameTable = &D_8016E25C;
                }
            }
        }
        initialize_actor_sprite_and_animation(object, object_data, placement, init_flags);
        runtime->unk_9A = 0xFF;
        runtime->unk_9C = -1;
        runtime->unk_8C = &D_8016B014;
        state->unk_1C = (s32)(state->unk_1C | 0x40000);
        runtime->unk_92 = -0x20;
        try_move_actor_to_valid_position(runtime, object_data, placement, state);
    }
    return state;
}

#include "dungeon/monster/clown/allocate_object_state.h"
#include "dungeon/monster/clown/allocate_object_state.h"

void *allocate_object_state_and_callbacks(s16 init_flags, s16 grid_x, s16 grid_y, s16 type_id)
{
    s32 mode;
    s32 state_flags;
    s32 update_flags;
    S_8014C878_3 *placement;
    S_8014C878_2 *config;
    void *object;
    S_8014C878_4 *extended_state;
    S_8014C878_1 *state;
    s8 saved_x;
    register s16 saved_type;
    s8 saved_y;

    state = 0;
    saved_x = grid_x;
    saved_type = type_id;
    saved_y = grid_y;
    object = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (object != 0) {
        state = object + 0x20;
        ((S_8014C878_0 *)object)->unk_10 = &D_8014CA58;
        state->unk_13 = 0x10;
        register_node(object, project_sprite_chain);
        config = ((S_8014C878_0 *)object)->unk_08;
        config->unk_0A = saved_type;
        placement = ((S_8014C878_0 *)object)->unk_0C;
        mode = init_flags & 3;
        placement->unk_25 = saved_y;
        extended_state = state;
        placement->unk_2C = &D_8015020C;
        placement->unk_24 = saved_x;
        if (mode == 1) {
            state_flags = state->unk_14 | 0x6000;
            update_flags = state->unk_1C | 0x6000;
            state->unk_14 = state_flags;
            state->unk_1C = update_flags;
        } else if (mode >= 2) {
            state_flags = state->unk_14 | 0x2000;
            update_flags = state->unk_1C | 0x2000;
            state->unk_14 = state_flags;
            state->unk_1C = update_flags;
        } else if (((init_flags & ~3) << 0x10) == 0) {
            if (!(state->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    set_or_clear_actor_status_slot(state, 1, (generate_random_value() & 0x3F) | 0x20);
                    placement->unk_2C = &D_8015025C;
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

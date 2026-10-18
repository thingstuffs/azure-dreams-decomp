#include "modules/dungeon_ovl_7f535800.h"

void *func_80158878(s16 init_flags, s16 pos_x, s16 pos_y, s16 init_value)
{
    s32 init_mode;
    s32 state_flags;
    s32 update_flags;
    S_80158878_3 *placement_data;
    S_80158878_2 *config_data;
    void *object;
    S_80158878_4 *extended_state;
    S_80158878_1 *state;
    s8 saved_x;
    register s16 saved_value;
    s8 saved_y;

    state = 0;
    saved_x = pos_x;
    saved_value = init_value;
    saved_y = pos_y;
    object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (object != 0) {
        state = object + 0x20;
        ((S_80158878_0 *)object)->unk_10 = &D_80158A58;
        state->unk_13 = 0x10;
        func_8004491C(object, func_80045340);
        config_data = ((S_80158878_0 *)object)->unk_08;
        config_data->unk_0A = saved_value;
        placement_data = ((S_80158878_0 *)object)->unk_0C;
        init_mode = init_flags & 3;
        placement_data->unk_25 = saved_y;
        extended_state = state;
        placement_data->unk_2C = &D_8015C20C;
        placement_data->unk_24 = saved_x;
        if (init_mode == 1) {
            state_flags = state->unk_14 | 0x6000;
            update_flags = state->unk_1C | 0x6000;
            state->unk_14 = state_flags;
            state->unk_1C = update_flags;
        } else if (init_mode >= 2) {
            state_flags = state->unk_14 | 0x2000;
            update_flags = state->unk_1C | 0x2000;
            state->unk_14 = state_flags;
            state->unk_1C = update_flags;
        } else if (((init_flags & ~3) << 0x10) == 0) {
            if (!(state->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    set_or_clear_actor_status_slot(state, 1, (generate_random_value() & 0x3F) | 0x20);
                    placement_data->unk_2C = &D_8015C25C;
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

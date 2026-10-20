#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"


typedef struct {
    void *callback;
    u8 pad04[4];
    u16 mode;
    u16 timer;
    u8 pad0C[4];
    u16 direction;
} State;

typedef struct {
    u8 pad00[10];
    s16 height;
    s32 x;
    s32 y;
    s32 value;
} Actor;

extern u8 D_800CFCEE;
extern s32 D_80100E20;
extern u8 D_800A5DF8;

extern s32 scale_random_to_unsigned_halfword_limit();
extern s32 runtime_estimate_vector_length();
extern void SD_Call();
extern s32 read_map_cell_at_world_position();
extern void add_a_directional_step_vector_scale_down_exceeds_length_limit();
extern void move_both_components_toward_zero_direction_dependent_steps_clamping_zero();
extern void add_hex_20000_s_signed_offset_hex_14();
extern void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2();
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
extern void compute_and_clamps_vector_based_adjustment_updates_town();
extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();
extern void spawn_directional_effects();
extern s32 compute_height_based_offset();
extern s32 check_masked_value_in_current_range();


/* Update actor movement, height, turning, and action state from input. */
void update_actor_movement_and_actions(State *state, Actor *actor) {
    GameWork *input;
    s32 speed;
    s16 height_limit;
    s32 direction;
    s32 world_value;
    s32 sound_period;

    input = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(actor);

    state->timer--;
    if ((s16)state->timer <= 0) {
        state->timer = scale_random_to_unsigned_halfword_limit(3) + 5;
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(2) + 2);
    }

    direction = (((u16)input->view.viewAngle) + 0x800) & 0xFFF;
    *(u16 *)((u8 *)state + 0x10) = direction;

    if (((u32)input->buttons) & 0x20) {
        add_a_directional_step_vector_scale_down_exceeds_length_limit(direction, D_80100E20, actor);
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(1));
    }

    if (((u32)input->buttons) & 0x10) {
        move_both_components_toward_zero_direction_dependent_steps_clamping_zero(actor);
        if ((((u32)input->buttons) & 0x30) == 0x20) {
            move_both_components_toward_zero_direction_dependent_steps_clamping_zero(actor);
        }
    } else {
        move_both_components_toward_zero_direction_dependent_steps_clamping_zero(actor);
    }
    height_limit = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, ((u8 *)&D_800FE488));
    if (actor->height >= height_limit) {
        compute_and_clamps_vector_based_adjustment_updates_town(actor, height_limit, ((u8 *)&D_800FE488));
    } else if ((&D_800CFCEE)[1] != 0) {
        actor->value = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(actor);
    } else {
        add_hex_20000_s_signed_offset_hex_14(actor);
    }
    world_value = read_map_cell_at_world_position(D_80083780.x.w.i, D_80083780.y.w.i);
    if (check_masked_value_in_current_range((u16)world_value) != 0) {
        actor->value -= compute_height_based_offset(actor);
    }

    speed = runtime_estimate_vector_length(actor->x, actor->y);
    if (D_80100E20 != 0) {
        {
            s32 speed_delta;
            speed_delta = D_80100E20 - speed;
            sound_period = (((speed_delta < 0 ? -speed_delta : speed_delta) * 7) / D_80100E20) + 2;
        }
        {
            u16 tick_count;
            tick_count = input->unk_004;
            if ((tick_count % sound_period) == 0) {
                SD_Call(0x60A);
            }
        }
    }

    if (speed == 0) {
        input->view.viewAngle = (((u16)input->view.viewAngle) + 8) & 0xFFF0;
    } else {
        if ((((u32)input->buttons) & 0x30) == 0x10) {
            speed = (D_80100E20 * 3) / 2;
        }
    }
    {
        s32 rounded_speed;
        rounded_speed = speed;
        if (speed < 0) {
            s32 rounding_bias;
            rounding_bias = 0xFFFF;
            rounded_speed = speed + rounding_bias;
        }
        speed = rounded_speed >> 16;
    }

    if ((*(u32 *)((u8 *)input + 8)) & 0x2000) {
        {
            s32 angle;
            angle = ((u16)input->view.viewAngle);
            angle = angle - 0x10;
            angle = angle - speed;
            input->view.viewAngle = angle;
        }
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(1));
    }

    if ((*(u32 *)((u8 *)input + 8)) & 0x8000) {
        {
            s32 angle;
            angle = ((u16)input->view.viewAngle);
            angle = angle + 0x10;
            angle = angle + speed;
            input->view.viewAngle = angle;
        }
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(1));
    }

    if ((((u32)input->unk_010) & 0x10) && (D_800CFCEE == 0)) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 1;
        return;
    }

    if (((u32)input->unk_010) & 0x100) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 0;
    }
}

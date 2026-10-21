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

extern u8 town_blocked_directions;
extern s32 town_movement_speed;
extern u8 D_800A5DF8;

extern s32 scale_random_to_unsigned_halfword_limit();
s32 runtime_estimate_vector_length(s32, s32);
extern void SD_Call();
s32 read_map_cell_at_world_position(s16, s16);
extern void add_a_directional_step_vector_scale_down_exceeds_length_limit();
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"
extern void add_hex_20000_s_signed_offset_hex_14();
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
void spawn_directional_effects(void *, s32);
struct EntityRec; s32 compute_height_based_offset(struct EntityRec *);
s32 check_masked_value_in_current_range(s32);


/* Update actor movement, height, turning, and action state from input. */
void update_actor_movement_and_actions(State *state, Actor *actor) {
    GameWork *input;
    s32 speed;
    s16 height_limit;
    s32 direction;
    s32 world_value;
    s32 sound_period;

    input = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile((struct EntityRec *)(actor));

    state->timer--;
    if ((s16)state->timer <= 0) {
        state->timer = scale_random_to_unsigned_halfword_limit(3) + 5;
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(2) + 2);
    }

    direction = (((u16)input->view.camera_rotation.parts.viewAngle) + 0x800) & 0xFFF;
    *(u16 *)((u8 *)state + 0x10) = direction;

    if (((u32)input->buttons) & 0x20) {
        add_a_directional_step_vector_scale_down_exceeds_length_limit(direction, town_movement_speed, actor);
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(1));
    }

    if (((u32)input->buttons) & 0x10) {
        move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
        if ((((u32)input->buttons) & 0x30) == 0x20) {
            move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
        }
    } else {
        move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
    }
    height_limit = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, ((u8 *)&position_query_scratch));
    if (actor->height >= height_limit) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(actor), height_limit, (struct TownVec * *)(((u8 *)&position_query_scratch)));
    } else if ((&town_blocked_directions)[1] != 0) {
        actor->value = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(actor));
    } else {
        add_hex_20000_s_signed_offset_hex_14(actor);
    }
    world_value = read_map_cell_at_world_position(view_reference_entity.x.w.i, view_reference_entity.y.w.i);
    if (check_masked_value_in_current_range((u16)world_value) != 0) {
        actor->value -= compute_height_based_offset((struct EntityRec *)(actor));
    }

    speed = runtime_estimate_vector_length(actor->x, actor->y);
    if (town_movement_speed != 0) {
        {
            s32 speed_delta;
            speed_delta = town_movement_speed - speed;
            sound_period = (((speed_delta < 0 ? -speed_delta : speed_delta) * 7) / town_movement_speed) + 2;
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
        input->view.camera_rotation.parts.viewAngle = (((u16)input->view.camera_rotation.parts.viewAngle) + 8) & 0xFFF0;
    } else {
        if ((((u32)input->buttons) & 0x30) == 0x10) {
            speed = (town_movement_speed * 3) / 2;
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
            angle = ((u16)input->view.camera_rotation.parts.viewAngle);
            angle = angle - 0x10;
            angle = angle - speed;
            input->view.camera_rotation.parts.viewAngle = angle;
        }
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(1));
    }

    if ((*(u32 *)((u8 *)input + 8)) & 0x8000) {
        {
            s32 angle;
            angle = ((u16)input->view.camera_rotation.parts.viewAngle);
            angle = angle + 0x10;
            angle = angle + speed;
            input->view.camera_rotation.parts.viewAngle = angle;
        }
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(1));
    }

    if ((((u32)input->pressed_buttons) & 0x10) && (town_blocked_directions == 0)) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 1;
        return;
    }

    if (((u32)input->pressed_buttons) & 0x100) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 0;
    }
}

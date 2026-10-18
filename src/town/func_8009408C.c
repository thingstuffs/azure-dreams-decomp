#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"



s32 scale_random_to_unsigned_halfword_limit();
void func_80094048(s32 **record, void *ptr, void *ptr2);
void initialize_action_object(s32 **record, void *ptr, void *ptr2);
void trigger_event_hex_519_interval_multiples_enabled();
void store_the_valid_shared_angle_in_offset_hex_10();
void call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58();
void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides();
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
void compute_and_clamps_vector_based_adjustment_updates_town();
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();
void spawn_radial_effect_objects();
extern u8 D_800CFCEF[];
extern u8 D_800D043C[];
extern s32 D_800FE4E0;


typedef struct S_800917EC_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800917EC_2;

/* Updates actor height, emits periodic effects, and handles the active state. */
void update_actor_with_periodic_effect(Rec_func_80094268_arg0 *actor, EntityRec *position, s32 context) {
    GameWork *state = &g_game_work;
    s16 surface_height;
    s16 action_timer;
    s32 *effect_pos;
    s32 state_flags;
    u16 effect_timer;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(position);
    move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(position);
    surface_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(position, ((u8 *)&D_800FE488));
    if ((surface_height - position->z.w.i) >= 4) {
        if (D_800CFCEF[0] == 0) {
            initialize_action_object(actor, position, context);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town(position, surface_height, ((u8 *)&D_800FE488));
    }
    effect_timer = actor->unk_0A.as_u16 - 1;
    actor->unk_0A.as_u16 = effect_timer;
    if ((effect_timer << 0x10) <= 0) {
        actor->unk_0A.as_u16 = (u16)(scale_random_to_unsigned_halfword_limit(4) + 3);
        D_800FE4E0 = position->x.v;
        effect_pos = &D_800FE4E0;
        ((S_800917EC_2 *)effect_pos)->unk_04 = position->y.v;
        ((S_800917EC_2 *)effect_pos)->unk_08 =
            position->z.v + 0xFFB00000;
        spawn_radial_effect_objects(effect_pos, D_800D043C,
                      (scale_random_to_unsigned_halfword_limit(2) & 0xFFFF) + 2);
    }
    state_flags = state->buttons;
    if ((state_flags & 0xF000) && (state_flags & 0x20)) {
        action_timer = actor->unk_3E.as_u16 - 1;
        actor->unk_3E.as_u16 = (u16)action_timer;
        trigger_event_hex_519_interval_multiples_enabled(action_timer, 8);
        store_the_valid_shared_angle_in_offset_hex_10(actor);
        call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(position);
        return;
    }
    func_80094048(actor, position, context);
}

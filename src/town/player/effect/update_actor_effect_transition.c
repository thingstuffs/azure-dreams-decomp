#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"

typedef struct S_800A5DF8_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A5DF8_0;

typedef struct S_800A5DF8_1 {
    u8 unk_00;
} S_800A5DF8_1;   /* &D_800CFCEF in update_actor_effect_transition */

typedef struct S_800A5DF8_4 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5DF8_4;


s32 read_map_cell_at_world_position(s16, s16);                        /* extern */
s16 step_angle_12_toward();           /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"                      /* extern */
void add_hex_20000_s_signed_offset_hex_14();                 /* extern */
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                 /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
struct EntityRec; s32 compute_height_based_offset(struct EntityRec *);                          /* extern */
struct EntityRec; void initialize_effect_and_adjust_value(void *, struct EntityRec *, s32);                         /* extern */
s32 check_masked_value_in_current_range(s32);                             /* extern */
extern u8 D_800A5FDC[];

/* Updates the actor effect and eases scene values before advancing the state. */
void update_actor_effect_transition(S_800A5DF8_4 *state, S_800A5DF8_0 *actor, s32 context) {
    s16 threshold;
    s32 offset_step;
    s16 angle;
    s32 next_offset;
    u16 ticks_left;
    register GameWork *scene_state;
    register u8 *effect_data;

    scene_state = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile((struct EntityRec *)(actor));
    effect_data = ((u8 *)&D_800FE488);
    threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, effect_data);
    if (actor->unk_0A >= threshold) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(actor), threshold, (struct TownVec * *)(effect_data));
    } else if (((S_800A5DF8_1 *)(&D_800CFCEF))->unk_00 != 0) {
        actor->unk_14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(actor));
    } else {
        add_hex_20000_s_signed_offset_hex_14(actor);
    }

    if (check_masked_value_in_current_range(read_map_cell_at_world_position(D_80083780.x.w.i, D_80083780.y.w.i) & 0xFFFF) != 0) {
        offset_step = actor->unk_14 - compute_height_based_offset((struct EntityRec *)(actor));
        actor->unk_14 = offset_step;
    }
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
    angle = step_angle_12_toward(scene_state->view.viewAngle, 0, 0x80);
    scene_state->view.viewAngle = angle;
    if ((angle & 0xFFF) < 0x80) {
        scene_state->view.viewAngle = 0;
    }
    ticks_left = state->unk_0A.s - 1;
    state->unk_0A.s = ticks_left;
    {
        s32 shifted_ticks;
        s32 ticks;
        shifted_ticks = (s32) ticks_left << 16;
        ticks = shifted_ticks >> 16;
        offset_step = -0x280;
        if (ticks <= 0) {
            state->unk_0A.u = 0;
        }
        next_offset = ticks > 0
            ? (offset_step -= scene_state->view.unk_0AC, offset_step /= ticks,
               ((u16)scene_state->view.unk_0AC) + offset_step)
        : -0x280;
        scene_state->view.unk_0AC = next_offset;
    }
    if ((state->unk_0A.u == 0) &&
        (scene_state->view.viewAngle == 0)) {
        if (state->unk_08 != 0) {
            initialize_effect_and_adjust_value(state, (struct EntityRec *)(actor), context);
        } else {
            state->unk_0A.u = 0;
            state->unk_00 = D_800A5FDC;
        }
    }

    return;
}

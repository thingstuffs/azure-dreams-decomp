#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "m2c_compat.h"

typedef struct S_800A58CC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A58CC_0;   /* (void *) shared_s0 in update_object_view_transition */

typedef struct S_800A58CC_2 {
    void * unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800A58CC_2;   /* arg0 in update_object_view_transition */


s32 read_map_cell_at_world_position(s16, s16);                        /* extern */
s16 step_angle_12_toward();               /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"                      /* extern */
void add_hex_20000_s_signed_offset_hex_14();                 /* extern */
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                 /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
struct EntityRec; s32 compute_height_based_offset(struct EntityRec *);                          /* extern */
s32 check_masked_value_in_current_range(s32);                             /* extern */
extern s32 D_800A5A98;
extern u8 D_800D0000[];
extern int abs(int);

/* Updates the object and interpolates town angles before advancing the state. */
void update_object_view_transition(S_800A58CC_2 *state_arg, void *object) {
    s16 threshold;
    s32 pitch_step;
    s16 yaw;
    s32 object_ref;
    s32 target_yaw;
    s32 yaw_delta;
    s32 pitch;
    u16 ticks;
    GameWork *town;
    ObjectPosition *coords;

         /* MATCH: Order the s2 parameter copy before the s0 copy. */
    object_ref = (s32) object;
    town = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile((void *) object_ref);
    threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated((void *) object_ref, &D_800FE488);
    if (((S_800A58CC_0 *)((void *) object_ref))->unk_0A >= threshold) {
        compute_and_clamps_vector_based_adjustment_updates_town((void *) object_ref, threshold, (struct TownVec * *)(&D_800FE488));
    } else {
        if (D_800D0000[-0x311] != 0) {
            ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = 0;
            clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((void *) object_ref);
        } else {
            add_hex_20000_s_signed_offset_hex_14((void *) object_ref);
        }
    }
    coords = &D_80083780;
    if (check_masked_value_in_current_range(read_map_cell_at_world_position(coords->x.w.i, coords->y.w.i) & 0xFFFF) != 0) {
        pitch_step = ((S_800A58CC_0 *)((void *) object_ref))->unk_14 - compute_height_based_offset((void *) object_ref);
        ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = pitch_step;
    }
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero((void *) object_ref);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero((void *) object_ref);
    target_yaw = (state_arg->unk_10 - 0x800) & 0xFFF;
    yaw = step_angle_12_toward(town->view.camera_rotation.parts.viewAngle, target_yaw, 0x80);
    town->view.camera_rotation.parts.viewAngle = yaw;
    yaw_delta = abs((yaw & 0xFFF) - target_yaw);
    if (yaw_delta < 0x80) {
        town->view.camera_rotation.parts.viewAngle = target_yaw;
    }
    ticks = state_arg->unk_0A.s - 1;
    state_arg->unk_0A.s = ticks;
    {
        s32 shifted_ticks;
        s32 ticks_left;
        shifted_ticks = (s32) ticks << 16;
        ticks_left = shifted_ticks >> 16;
        pitch_step = -0x2B0;
        if (ticks_left <= 0) {
            state_arg->unk_0A.u = 0;
        }
        pitch = ticks_left > 0
            ? (pitch_step -= town->view.camera_rotation.parts.camera_rotation_x, pitch_step /= ticks_left,
               ((u16)town->view.camera_rotation.parts.camera_rotation_x) + pitch_step)
        : -0x2B0;
        town->view.camera_rotation.parts.camera_rotation_x = pitch;
    }
    if ((state_arg->unk_0A.u == 0) && (town->view.camera_rotation.parts.viewAngle == target_yaw)) {
        state_arg->unk_0A.u = 0;
        state_arg->unk_00 = &D_800A5A98;
    }
}

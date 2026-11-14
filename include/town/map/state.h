#ifndef TOWN_MAP_STATE_H
#define TOWN_MAP_STATE_H
/* Prototypes of the functions defined in src/town/map/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"
#include "shared/entity.h"

struct S_800BDFA0_0;
struct S_func_800A9624_1;
struct SpriteFrameState;
struct TownCameraState;
struct MapSecondaryCallbackState;
struct TownPropAnimationActor;

/* fill_wrapped_tile_pair.c */
void fill_wrapped_tile_pair(s16 start_x, s16 start_y, s16 mode, s32 pair_index);

/* cycle_prop_animation_until_done.c */
void cycle_prop_animation_until_done(struct TownPropAnimationActor *self, s32 unused_value, SpriteFrameState *destination);

/* flag_nodes_by_id.c */
void flag_nodes_by_id(s32 id);

/* initialize_white_points_effect.c */
void initialize_white_points_effect(void *body, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);

/* initialize_town_camera_states.c */
void initialize_town_camera_states(void);

/* initialize_secondary_view_state.c */
void initialize_secondary_view_state(struct MapSecondaryCallbackState *state);

/* initialize_randomized_velocity_object.c */
void initialize_randomized_velocity_object(TownObjectRecord *object, ObjectPosition *random_state, SpriteFrameState *settings);

/* cycle_prop_animation.c */
void cycle_prop_animation(struct S_800BDFA0_0 *record, s32 unused, SpriteFrameState *value);

/* initialize_midpoint_tracking.c */
void initialize_midpoint_tracking(struct TownCameraState *state);

/* run_prop_callback_or_retire.c */
void run_prop_callback_or_retire(struct S_func_800A9624_1 *object, s32 state_arg, s32 callback_arg);

/* retire_record_when_status_clear.c */
void retire_record_when_status_clear(void *record);

/* select_flag_test_page_and_redraw_grid.c */
s32 select_flag_test_page_and_redraw_grid(void);

/* store_state_and_update_grid_center.c */
void store_state_and_update_grid_center(s8 state);

/* spin_object_until_outside_bounds.c */
void spin_object_until_outside_bounds(void *object, void *context);

/* fade_sprite_until_animation_ends.c */
void fade_sprite_until_animation_ends(void *flags_end, ObjectPosition *unused, SpriteFrameState *state);

#endif

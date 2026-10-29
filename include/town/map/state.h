#ifndef TOWN_MAP_STATE_H
#define TOWN_MAP_STATE_H
/* Prototypes of the functions defined in src/town/map/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/sprite_frame_state.h"

struct S_800BDFA0_0;
struct S_func_800A9624_1;
struct SpriteFrameState;
struct TownCameraState;
struct TownPropAnimationActor;

/* apply_item_and_update_matching_actor_state.c */
void apply_item_and_update_matching_actor_state(s16 start_x, s16 start_y, s16 mode, s32 pair_index);

/* copy_record_state_to_destination.c */
void copy_record_state_to_destination(struct TownPropAnimationActor *self, s32 unused_value, SpriteFrameState *destination);

/* flag_nodes_by_id.c */
void flag_nodes_by_id(s32 id);

/* initialize_object_header_and_state.c */
void initialize_object_header_and_state(void *body, void *placement, struct SpriteFrameState *unused_sprite);

/* initialize_paired_state_blocks.c */
void initialize_paired_state_blocks(void);

/* initialize_paired_state_callbacks.c */
void initialize_paired_state_callbacks(void *state);

/* initialize_randomized_object_state.c */
void initialize_randomized_object_state(void *object, void *random_state, void *settings);

/* initialize_record_visual_state.c */
void initialize_record_visual_state(struct S_800BDFA0_0 *record, s32 unused, SpriteFrameState *value);

/* initialize_transition_state.c */
void initialize_transition_state(struct TownCameraState *state);

/* process_object_state_or_fallback.c */
void process_object_state_or_fallback(struct S_func_800A9624_1 *object, s32 state_arg, s32 callback_arg);

/* process_zero_status_record.c */
void process_zero_status_record(void *record);

/* select_flag_test_page_and_redraw_grid.c */
s32 select_flag_test_page_and_redraw_grid(void);

/* store_state_and_update_grid_center.c */
void store_state_and_update_grid_center(s8 state);

/* update_object_link_or_angle_state.c */
void update_object_link_or_angle_state(void *object, void *context);

/* update_state_and_set_flags.c */
void update_state_and_set_flags(void *flags_end, void *unused, SpriteFrameState *state);

#endif

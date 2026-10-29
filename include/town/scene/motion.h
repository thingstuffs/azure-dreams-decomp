#ifndef TOWN_SCENE_MOTION_H
#define TOWN_SCENE_MOTION_H
/* Prototypes of the functions defined in src/town/scene/motion/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"

struct ColliderView;
struct CollisionOverlap;
struct CollisionScratch;
struct S_80019DE0_0;
struct ScenePositionEntry;
struct SpriteFrameState;

/* adjust_fixed_point_value_at_bounds.c */
void adjust_fixed_point_value_at_bounds(s32 context, s32 *value);

/* advance_player_position_b.c */
void advance_player_position_b(void);

/* advance_three_component_motion.c */
void advance_three_component_motion(void *timer_state, void *motion);
void func_8052FC8C(void *timer_state, void *motion);

/* apply_entry_position.c */
s32 apply_entry_position(struct ScenePositionEntry *entries, void *object, void *context, s32 selection);

/* blend_position_and_trace.c */
void blend_position_and_trace(s32 first_input, s32 second_input, s32 blend_weight, s32 remaining_weight);

/* build_visible_tile_quads.c */
void initialize_scene_slot_45(void *object, void *unused, struct SpriteFrameState *context);

/* check_scene_callback_and_position.c */
s32 check_scene_callback_and_position(void);

/* check_the_position_second_coordinate_adjusted_stored_offset.c */
s16 check_the_position_second_coordinate_adjusted_stored_offset(void *source_record);

/* copy_callback_value_to_destination.c */
void copy_callback_value_to_destination(s32 destination, s32 *values);

/* copy_selected_row_to_player_position.c */
void copy_selected_row_to_player_position(void);

/* draw_wrapped_tile_column.c */
void draw_wrapped_tile_column(s16 column, s16 row, s16 scroll_y);

/* enable_position_offset.c */
void enable_position_offset(void);

/* get_smallest_signed_overlap_axis_amount_two_intersecting_boxes.c */
struct CollisionOverlap *get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(void *first_box, void *second_box);

/* handle_evaluate_position_after_subtracting_stored_offset_first_component.c */
s16 handle_evaluate_position_after_subtracting_stored_offset_first_component(void *position);

/* handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis.c */
void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(struct ColliderView *collider, ObjectPosition *position);

/* motion.c */
void play_timed_sound_sequence(void *record);

/* place_player_at_fixed_position.c */
void set_player_fixed_position(void);

/* run_scene_callback_with_position_shift.c */
void run_scene_callback_with_position_shift(void);

/* scale_scene_position.c */
void scale_scene_position(void);

/* set_active_position_state_record.c */
void set_active_position_state_record(void);

/* set_player_position_record.c */
void set_player_position_record(void);

/* shift_scene_position.c */
void shift_scene_position(void);

/* submit_player_position_record.c */
void submit_player_position_record(void);

/* submit_position_record_copy.c */
void submit_position_record_copy(void);

/* update_first_axis_slot_value.c */
void update_first_axis_slot_value(struct ColliderView *collider, ObjectPosition *position, struct CollisionScratch *entry);

/* update_motion_and_brightness.c */
void update_motion_and_brightness(void *object, void *motion, void *visual);

/* update_second_axis_slot_value.c */
void update_second_axis_slot_value(struct ColliderView *collider, ObjectPosition *position, struct CollisionScratch *entry);

#endif

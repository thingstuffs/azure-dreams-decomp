#ifndef TOWN_PERSON_OBJECT_H
#define TOWN_PERSON_OBJECT_H
struct TownObjectRecord;
/* Prototypes of the functions defined in src/town/person/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_80082D58.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"

struct TownObjectRecord;
struct S_800C2864_0;
struct S_800C3960_0;
struct SpriteFrameState;

/* advance_and_clamp_entity_value.c */
void advance_and_clamp_entity_value(TownObjectRecord *context, ObjectPosition *object, SpriteFrameState *update_data);

/* advance_entity_countdown.c */
void advance_entity_countdown(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *update_data);

/* advance_object_and_run_follow_up.c */
void advance_object_and_run_follow_up(TownObjectRecord *object, ObjectPosition *motion, SpriteFrameState *sprite);

/* apply_object_setup_and_update.c */
void apply_object_setup_and_update(TownObjectRecord *object, ObjectPosition *update_context, SpriteFrameState *setup_context);

/* init_person_target_move.c */
void init_person_target_move(struct TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);
void func_800C4804(struct TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);

/* set_person_descriptor_tables.c */
void set_person_descriptor_tables(struct TownObjectRecord *object);

/* assign_object_data_pointers.c */
void set_object_data_tables_with_link(struct TownObjectRecord *object);

/* call_object_callback.c */
void call_object_callback(struct S_800C3960_0 *object, ObjectPosition *context, SpriteFrameState *motion);

/* check_active_transform_object.c */
s32 check_active_transform_object(TownObjectRecord *other);

/* clear_object_slot_and_mark_removed.c */
void clear_object_slot_and_mark_removed(void *object);

/* clear_object_slot_and_run_callbacks.c */
void clear_object_slot_and_run_callbacks(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* create_person_object.c */
void create_person_object(void);

/* finalize_transform_object_or_callback.c */
void finalize_transform_object_or_callback(void *object, ObjectPosition *position, struct SpriteFrameState *sprite);

/* forward_object_setup_arguments.c */
void forward_object_setup_arguments(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *update_data);

/* forward_to_select_setup_path.c */
void forward_to_select_setup_path(TownObjectRecord *object, ObjectPosition *value_1, SpriteFrameState *value_2, s32 value_3);

/* update_reaction_vertical_ease.c */
void update_reaction_vertical_ease(TownObjectRecord *object);

/* initialize_mother_event_object.c */
void initialize_mother_event_object(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* load_entries_and_advance_state.c */
void load_entries_and_advance_state(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *sprite);

/* initialize_orbiting_object.c */
void initialize_orbiting_object(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* register_object_slot_with_tables.c */
void func_800C3050(struct TownObjectRecord *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
void register_object_slot_with_tables(struct TownObjectRecord *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);

/* reset_heading_and_update_object.c */
void reset_heading_and_update_object(TownObjectRecord *object, ObjectPosition *update_context, SpriteFrameState *setup_context);

/* start_person_jump.c */
void start_person_jump(TownObjectRecord *object, ObjectPosition *state, struct SpriteFrameState *sprite);

/* init_mia_person.c */
void init_mia_person(TownObjectRecord *object, ObjectPosition *position_unused, struct SpriteFrameState *sprite_unused);

/* initialize_actor_response_object.c */
void initialize_actor_response_object(TownObjectRecord *object, ObjectPosition *followupValue, SpriteFrameState *sprite);

/* start_random_wait_select_setup.c */
void start_random_wait_select_setup(struct TownObjectRecord *object, ObjectPosition *unusedArg, SpriteFrameState *initValue);

/* initialize_bounce_reaction_object.c */
void initialize_bounce_reaction_object(TownObjectRecord *object, ObjectPosition *state, SpriteFrameState *sprite);

/* initialize_object_handlers.c */
void initialize_object_handlers(TownObjectRecord *object, ObjectPosition *unused_context, SpriteFrameState *unused_setup);

/* initialize_object_referenced_data_pointers.c */
void initialize_object_referenced_data_pointers(struct TownObjectRecord *object, ObjectPosition *unused_context, struct SpriteFrameState *unused_output);

/* initialize_object_resources_g01178.c */
void initialize_camera_chase_object(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *display_state);
void set_camera_chase_data(TownObjectRecord *object, ObjectPosition *chase_data, SpriteFrameState *request_param, s32 check_param);
void clear_slot_flag_and_update(struct TownObjectRecord *obj, struct ObjectPosition *position, struct SpriteFrameState *sprite);
void accelerate_to_lower_limit(TownObjectRecord *context, ObjectPosition *record, SpriteFrameState *callback_arg);
void init_actor_handler_state(struct TownObjectRecord *actor, ObjectPosition *state);
void *create_gray_sprite_user_object(s32 user_data);

/* initialize_object_slot_and_display.c */
void init_far_with_follower_sprite(TownObjectRecord *object, ObjectPosition *unused_a, struct SpriteFrameState *unused_b);

/* initialize_object_slot_data.c */
void init_far_person(TownObjectRecord *object, ObjectPosition *unused_1, struct SpriteFrameState *unused_2);

/* initialize_object_sprite.c */
void initialize_object_sprite(Rec_D_800CFCB4 *object, ObjectPosition *context, SpriteFrameState *sprite);

/* initialize_object_tables.c */
void initialize_object_tables(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* init_reaction_object_with_z_velocity.c */
void init_reaction_object_with_z_velocity(TownObjectRecord *object, ObjectPosition *motion, SpriteFrameState *sprite);

/* initialize_reaction_object.c */
void initialize_reaction_object(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* initialize_reaction_object_type.c */
void init_reaction_object_with_timer(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* initialize_reaction_object_type_a.c */
void init_reaction_object_slot_clut(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *state);

/* initialize_reaction_object_type_f.c */
void initialize_scene_slot_79(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *stateValues);

/* initialize_transform_object.c */
void initialize_transform_object(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

/* initialize_transform_object_values.c */
void initialize_transform_object_values(TownObjectRecord *object, ObjectPosition *setup_context, SpriteFrameState *unused);

/* initialize_variant_object.c */
void initialize_variant_object(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

/* is_default_object_data.c */
s32 is_default_object_data(TownObjectRecord *object);

/* process_checked_transform_object.c */
void process_checked_transform_object(void *object, s32 check_value_1, s32 check_value_2, s32 check_value_3);

/* process_transform_object_on_zero.c */
void process_transform_object_on_zero(void *object, s32 value, s32 options, s32 mode);

/* reset_matching_transform_object.c */
void reset_matching_transform_object(s32 object_addr);

/* reset_object_handler_after_update.c */
void reset_object_handler_after_update(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *output);

/* reset_object_handler_field_c_value.c */
void restart_person_countdown_update(TownObjectRecord *object, struct ObjectPosition *unused_position, SpriteFrameState *updateValue);

/* reset_object_handler_field_c_value_ee.c */
void start_person_jump_countdown(TownObjectRecord *object, struct ObjectPosition *unused_position, SpriteFrameState *updateValue);

/* reset_object_handler_field_value.c */
void reset_person_heading_half_turn(TownObjectRecord *object, struct ObjectPosition *unused_position, SpriteFrameState *updateValue);

/* reset_object_handler_field_value_b.c */
void reset_person_heading_quarter_turn(TownObjectRecord *object, struct ObjectPosition *unused_position, SpriteFrameState *updateValue);

/* reset_person_descriptor_entries.c */
void reset_person_descriptor_entries(struct TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *output);

/* reset_person_object_entries.c */
void reset_person_object_entries(void *object);

/* run_object_callback.c */
void run_object_callback(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *record);

/* select_object_setup_path.c */
s32 select_object_setup_path(TownObjectRecord *object, ObjectPosition *request_data, SpriteFrameState *request_param);

/* set_object_referenced_data_pointers.c */
void set_object_referenced_data_pointers(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

/* set_transform_object_data.c */
void set_transform_object_data(struct S_800C2864_0 *object);

/* store_object_slot_and_dispatch.c */
void store_object_slot_and_dispatch(TownObjectRecord *object, ObjectPosition *update_context, SpriteFrameState *sprite);

/* update_entity_countdown_completion.c */
void update_entity_countdown_completion(TownObjectRecord *entity, ObjectPosition *position, SpriteFrameState *sprite);

/* update_object_orbit_and_timer.c */
void update_object_orbit_and_timer(struct TownObjectRecord *object, ObjectPosition *position, void *update_arg, s32 check_param);

/* update_person_object.c */
void update_person_object(void *object, s32 update_ctx, SpriteFrameState *display);

/* update_transform_object_on_request.c */
void update_transform_object_on_request(void *object, s32 request_data, s32 request_param, s32 check_param);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void func_800C2E84(TownObjectRecord *state, SpriteFrameState *output, s32 *entries);
void initialize_object_entries(TownObjectRecord *state, SpriteFrameState *output, s32 *entries);

void interpolate_person_to_saved_position(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);

void unregister_and_update_object(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

void start_person_scale_animation(TownObjectRecord *object, s32 unused, SpriteFrameState *output);

extern s32 countdown_expiry_entry_group[];

void run_record_countdown_expiry(TownObjectRecord *record, ObjectPosition *position, struct SpriteFrameState *sprite);

void initialize_countdown_expiry_entry_group(TownObjectRecord *object, struct ObjectPosition *unused_position, struct SpriteFrameState *output);

extern s32 effect_spawn_countdown_entries[];

void start_effect_spawn_countdown(TownObjectRecord *actor, s32 unused, SpriteFrameState *output);

extern s32 entity_countdown_entries[];

void advance_counter_and_start_entity_countdown(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

#endif

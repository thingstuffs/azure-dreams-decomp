#ifndef TOWN_PERSON_OBJECT_H
#define TOWN_PERSON_OBJECT_H
/* Prototypes of the functions defined in src/town/person/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_80082D58.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"

struct PersonObject;
struct S_800C2664_0;
struct S_800C2864_0;
struct S_800C3960_0;
struct S_800C4F6C_2;
struct S_800C51DC_0;
struct S_800C51DC_1;
struct S_800C8928_0;
struct S_800C895C_0;
struct SpriteFrameState;

/* advance_and_clamp_entity_value.c */
void advance_and_clamp_entity_value(void *context, EntityRec *object, void *update_data);

/* advance_entity_countdown.c */
void advance_entity_countdown(Rec_func_80094268_arg0 *object, void *context, void *update_data);

/* advance_object_and_run_follow_up.c */
void advance_object_and_run_follow_up(Rec_func_80094268_arg0 *object, EntityRec *motion, s32 context);

/* apply_object_setup_and_update.c */
void apply_object_setup_and_update(void *object, void *update_context, void *setup_context);

/* apply_person_descriptor_tail.c */
void apply_person_descriptor_tail(struct PersonObject *object, ObjectPosition *position, SpriteFrameState *output);
void func_800C4804(struct PersonObject *object, ObjectPosition *position, SpriteFrameState *output);

/* assign_four_object_data_pointers.c */
void assign_four_object_data_pointers(struct S_800C8928_0 *object);

/* assign_object_data_pointers.c */
void assign_object_data_pointers_2(struct S_800C895C_0 *object);

/* call_object_callback.c */
void call_object_callback(struct S_800C3960_0 *object, void *context, void *motion);

/* check_active_transform_object.c */
s32 check_active_transform_object(void *other);

/* clear_object_slot_and_mark_removed.c */
void clear_object_slot_and_mark_removed(void *object);

/* clear_object_slot_and_run_callbacks.c */
void clear_object_slot_and_run_callbacks(Rec_D_80082D58 *object, void *callback_arg_1, void *callback_arg_2);

/* create_person_object.c */
void create_person_object(void);

/* finalize_transform_object_or_callback.c */
void finalize_transform_object_or_callback(void *object, s32 check_value, s32 callback_value);

/* forward_object_setup_arguments.c */
void forward_object_setup_arguments(void *object, void *context, void *update_data);

/* forward_object_update_values.c */
void forward_object_update_values(void *object, void *value_1, void *value_2, s32 value_3);

/* forward_reaction_object.c */
void forward_reaction_object(void *object);

/* initialize_mother_event_object.c */
void initialize_mother_event_object(Rec_func_80094268_arg0 *object, s32 unused, void *init_data);

/* initialize_object_and_advance.c */
void initialize_object_and_advance(void *object, s32 unused, void *context);

/* initialize_object_and_data_pointer.c */
void initialize_object_and_data_pointer(Rec_func_80094268_arg0 *object, s32 unused, void *init_value);

/* initialize_object_and_register_slot.c */
void func_800C3050(struct PersonObject *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
void initialize_object_and_register_slot(struct PersonObject *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);

/* initialize_object_and_update.c */
void initialize_object_and_update(void *object, void *update_context, void *setup_context);

/* initialize_object_callback.c */
void initialize_object_callback(Rec_func_80094268_arg0 *object, ObjectPosition *state, void *init_data);

/* initialize_object_configuration_x.c */
void initialize_object_configuration_x(struct PersonObject *object);

/* initialize_object_entries_and_handler.c */
void initialize_object_entries_and_handler(void *object, void *followupValue, void *setupValue);

/* initialize_object_from_context.c */
void initialize_object_from_context(void *object, EntityRec *unusedArg, void *initValue);

/* initialize_object_from_table_entry.c */
void initialize_object_from_table_entry(Rec_func_80094268_arg0 *object, ObjectPosition *state, void *init_data);

/* initialize_object_handlers.c */
void initialize_object_handlers(void *object, void *unused_context, void *unused_setup);

/* initialize_object_referenced_data_pointers.c */
void initialize_object_referenced_data_pointers(struct PersonObject *object, void *unused_context, struct SpriteFrameState *unused_output);

/* initialize_object_resources_g01178.c */
void initialize_object_resources_2(void *object, IntVector3 *position, struct S_800C4F6C_2 *display_state);
void set_camera_chase_data(void *object, void *chase_data, s32 request_param, s32 check_param);
void clear_object_slot_table_run(void *obj, void *param_a, void *param_b);
void accelerate_object_coordinates_to_lower_limits(void *context, EntityRec *record, void *callback_arg);
void init_actor_handler_state(struct S_800C51DC_0 *actor, struct S_800C51DC_1 *state);
void *create_user_data_object_b(s32 user_data);

/* initialize_object_slot_and_display.c */
void initialize_object_slot_9_and_display(void *object, void *unused_a, struct SpriteFrameState *unused_b);

/* initialize_object_slot_data.c */
void initialize_object_slot_9_data(void *object, void *unused_1, struct SpriteFrameState *unused_2);

/* initialize_object_sprite.c */
void initialize_object_sprite(Rec_D_800CFCB4 *object, void *context, SpriteFrameState *sprite);

/* initialize_object_tables.c */
void initialize_object_tables(void *object, s32 unused, void *init_value);

/* initialize_object_with_handler_and_offset.c */
void initialize_object_with_handler_and_offset(Rec_func_80094268_arg0 *object, ObjectPosition *motion, void *init_data);

/* initialize_reaction_object.c */
void initialize_reaction_object(Rec_func_80094268_arg0 *object, void *unused, void *context);

/* initialize_reaction_object_type.c */
void initialize_reaction_object_type_21(Rec_func_80094268_arg0 *object, s32 unused, void *context);

/* initialize_reaction_object_type_a.c */
void initialize_reaction_object_type_4_a(void *object, void *unused, struct SpriteFrameState *state);

/* initialize_reaction_object_type_f.c */
void initialize_reaction_object_type_4_f(void *object, void *unused, struct SpriteFrameState *stateValues);

/* initialize_transform_object.c */
void initialize_transform_object(void *object, void *unused_position, struct SpriteFrameState *unused_sprite);

/* initialize_transform_object_values.c */
void initialize_transform_object_values(struct S_800C2664_0 *object, void *setup_context, s32 unused);

/* initialize_variant_object.c */
void initialize_variant_object(void *body, void *unused_position, struct SpriteFrameState *unused_sprite);

/* is_default_object_data.c */
s32 is_default_object_data(Rec_func_80094268_arg0 *object);

/* process_checked_transform_object.c */
void process_checked_transform_object(void *object, s32 check_value_1, s32 check_value_2, s32 check_value_3);

/* process_transform_object_on_zero.c */
void process_transform_object_on_zero(void *object, s32 value, s32 options, s32 mode);

/* reset_matching_transform_object.c */
void reset_matching_transform_object(s32 object_addr);

/* reset_object_handler_after_update.c */
void reset_object_handler_after_update(void *object, s32 unused, void *updateValue);

/* reset_object_handler_field_c_value.c */
void reset_object_handler_field_6c_value_15(void *object, s32 unused, SpriteFrameState *updateValue);

/* reset_object_handler_field_c_value_ee.c */
void reset_object_handler_field_6c_value_15_46ee4(void *object, s32 unused, SpriteFrameState *updateValue);

/* reset_object_handler_field_value.c */
void reset_object_handler_field_72_value_800(void *object, s32 unused, SpriteFrameState *updateValue);

/* reset_object_handler_field_value_b.c */
void reset_object_handler_field_72_value_400(void *object, s32 unused, SpriteFrameState *updateValue);

/* reset_person_descriptor_entries.c */
void reset_person_descriptor_entries(struct PersonObject *object, s32 unused, SpriteFrameState *output);

/* reset_person_object_entries.c */
void reset_person_object_entries(void *object);

/* run_object_callback.c */
void run_object_callback(void *object, void *context, SpriteFrameState *record);

/* select_object_setup_path.c */
s32 select_object_setup_path(void *object, void *request_data, void *request_param);

/* set_object_referenced_data_pointers.c */
void set_object_referenced_data_pointers(Rec_func_80094268_arg0 *object, void *unused_context, struct SpriteFrameState *unused_sprite);

/* set_transform_object_data.c */
void set_transform_object_data(struct S_800C2864_0 *object);

/* store_object_slot_and_dispatch.c */
void store_object_slot_and_dispatch(void *object, void *update_context, void *setup_context);

/* update_entity_countdown_completion.c */
void update_entity_countdown_completion(Rec_func_80094268_arg0 *entity, void *update_context, void *setup_context);

/* update_object_orbit_and_timer.c */
void update_object_orbit_and_timer(void *object, void *position, void *update_arg, s32 check_param);

/* update_person_object.c */
void update_person_object(void *object, s32 update_ctx, SpriteFrameState *display);

/* update_transform_object_on_request.c */
void update_transform_object_on_request(void *object, s32 request_data, s32 request_param, s32 check_param);

#endif

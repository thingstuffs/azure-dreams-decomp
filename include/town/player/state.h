#ifndef TOWN_PLAYER_STATE_H
#define TOWN_PLAYER_STATE_H
/* Prototypes of the functions defined in src/town/player/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct EntityRec;
struct Rec_func_80094268_arg0;
struct S_800946FC_0;
struct S_80098C04_0;

/* advance_player_state.c */
void advance_player_state(struct Rec_func_80094268_arg0 *context, EntityRec *state, void *updateData);

/* clear_script_flag_bit.c */
void clear_script_flag_bit(s32 bit_index);

/* clear_shared_flag_and_initialize_object.c */
void clear_shared_flag_and_initialize_object(void *state, void *context, void *mode);

/* clear_the_global_state_s_fifth_word_copy_source_s_second.c */
void clear_the_global_state_s_fifth_word_copy_source_s_second(s32 *source);

/* create_familiar_deployment_effect_with_owner_state.c */
void create_familiar_deployment_effect_with_owner_state(void);

/* dispatch_sound_by_global_flag.c */
void dispatch_sound_by_global_flag(void);

/* ease_object_value_and_advance_state.c */
void ease_object_value_and_advance_state(void *state, void *object);

/* forward_state_value_to_handler_a.c */
void forward_state_value_to_handler_a(void *state, s32 value);

/* forward_state_value_to_handler_b.c */
void forward_state_value_to_handler_b(void *state, s32 value);

/* get_script_flag_mask.c */
s32 get_script_flag_mask(s32 flagIndex);

/* initialize_actor_action_state.c */
void initialize_actor_action_state(Rec_func_80094268_arg0 *object, ObjectPosition *state, s32 initData);

/* initialize_actor_interaction_state.c */
void initialize_actor_interaction_state_19(struct S_800946FC_0 *object);

/* initialize_mode_state_tables.c */
void initialize_mode_state_tables(void);

/* initialize_player_slot_state.c */
void initialize_player_slot_state(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);

/* initialize_record_and_clear_shared_flag.c */
void initialize_record_and_clear_shared_flag(Rec_func_80094268_arg0 *primary_value, struct EntityRec *secondary_value, void *context_value);

/* initialize_state_from_terminated_entries.c */
void initialize_state_from_terminated_entries(s32 *entries);

/* read_script_flag_range.c */
s32 read_script_flag_range(s32 start_index, s32 count);

/* reset_player_slot_state.c */
void reset_player_slot_state(Rec_func_80094268_arg0 *object, void *ptr, void *ptr2);

/* run_action_then_fallback_on_flag.c */
void run_action_then_fallback_on_flag(s32 *value, s32 context, SpriteFlagsView *record);

/* run_the_action_sequence_context_unless_flag_a_set.c */
s32 run_the_action_sequence_context_unless_flag_hex_a_5_set(s32 context);

/* select_next_item_state.c */
void select_next_item_state(void *object, void *position, void *context);

/* set_handler_counter_and_clear_flag.c */
void set_handler_counter_and_clear_flag(struct S_80098C04_0 *state, s32 target);

/* set_script_flag_bit.c */
void set_script_flag_bit(s32 bit_index);

/* set_state_bytes_from_flags.c */
void set_state_bytes_from_flags(s32 flags, u8 *state);

/* update_actor_action_state.c */
void update_actor_action_state(Rec_func_80094268_arg0 *state, EntityRec *motion, s32 callback_arg);

/* update_actor_and_dispatch_state.c */
void update_actor_and_dispatch_state(void *actor, EntityRec *record, s32 context);

/* update_actor_with_interaction_state.c */
void update_actor_with_interaction_state(Rec_func_80094268_arg0 *controller, EntityRec *entity, s32 context);

/* update_entity_and_dispatch_timed_state.c */
void update_entity_and_dispatch_timed_state(void *state, void *entity, void *transition_arg);

/* write_script_flag_range.c */
void write_script_flag_range(s32 base, s32 bits, s32 count);

#endif

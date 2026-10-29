#ifndef TOWN_PERSON_STATE_H
#define TOWN_PERSON_STATE_H
/* Prototypes of the functions defined in src/town/person/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct PersonObject;
struct ReactionState;
struct S_800AAE00_0;
struct S_800AAE00_1;
struct S_800C56A8_0;
struct S_800CA458_0;
struct S_800CA7D8_0;
struct S_800CCC34_0;
struct S_800CCCCC_0;
struct S_800CCD68_0;
struct S_800CCF18_0;
struct S_800CCF60_0;
struct S_800CEDA4_0;
struct SpriteFrameState;

/* adjust_two_state_values.c */
void adjust_two_state_values(Rec_func_80094268_arg0 *object, struct S_800C56A8_0 *state);

/* advance_four_phase_flag_sequence.c */
void advance_four_phase_flag_sequence(struct S_800CCD68_0 *sequence);

/* advance_reaction_state_and_cleanup.c */
void advance_reaction_state_and_cleanup(Rec_func_80094268_arg0 *object, struct S_800CA458_0 *state);

/* call_state_handler_and_set_four.c */
void call_state_handler_and_set_four(Rec_func_80094268_arg0 *object, s32 context, s32 update_data);

/* clear_flag_object_direction.c */
void clear_flag_object_direction(struct S_800CCF60_0 *state);

/* clear_record_indexed_flag.c */
void clear_record_indexed_flag(void *state, s32 unused_context, void *unused_state_context);

/* dispatch_status_triggered_handler.c */
void dispatch_status_triggered_handler(s32 object, s32 unused, SpriteFlagsView *status);

/* dispatch_status_triggered_update.c */
void dispatch_status_triggered_update(void *handler_arg, void *context, SpriteFlagsView *status);

/* forward_flag_state_update.c */
void forward_flag_state_update(void *object, void *context, void *update_data);

/* increment_flag_object_counter.c */
void increment_flag_object_counter(struct S_800CCCCC_0 *object);

/* initialize_actor_clear_shared_flag.c */
void initialize_actor_clear_shared_flag(Rec_func_80094268_arg0 *actor, s32 unused, void *init_param);

/* initialize_actor_clear_table_flag.c */
void initialize_actor_clear_table_flag(Rec_func_80094268_arg0 *actor, s32 unused, void *init_param);

/* initialize_actor_reaction_and_fixed_state.c */
void func_800CDF00(Rec_func_80094268_arg0 *actor, struct ReactionState *state, SpriteFrameState *output);
void initialize_actor_reaction_and_fixed_state(Rec_func_80094268_arg0 *actor, struct ReactionState *state, SpriteFrameState *output);

/* initialize_actor_state_table.c */
void initialize_actor_state_table(void *actor, s32 context, void *state_context);

/* initialize_entity_action_state.c */
void initialize_entity_action_state(void *entity, s32 unused, void *init_value);

/* initialize_indexed_callback_state.c */
void initialize_indexed_callback_state(void *object, s32 unused, void *initValue);

/* initialize_mother_event_object_state.c */
void initialize_mother_event_object_state(void *object, s32 unused, void *initializationArg);

/* initialize_object_assigns_state_data.c */
void initialize_object_assigns_state_data(Rec_func_80094268_arg0 *object, void *unusedArg, void *initializationArg);

/* initialize_person_state.c */
void initialize_person_state(void *state, void *output);

/* initialize_reaction_object_and_clear_flag.c */
void initialize_reaction_object_and_clear_flag(Rec_func_80094268_arg0 *object, s32 unused, void *context);

/* install_object_handler_and_clear_slot_flag.c */
void install_object_handler_and_clear_slot_flag(void *object);

/* install_update_after_flag_clear.c */
void install_update_after_flag_clear(struct PersonObject *object, ObjectPosition *position, SpriteFrameState *output);

/* invoke_flag_state_callback.c */
void invoke_flag_state_callback(struct S_800CCC34_0 *object, s32 context, void *motion);

/* invoke_state_indexed_callback.c */
void invoke_state_indexed_callback(void *object, void *context, void *motion);

/* process_object_flag_bits.c */
void process_object_0x6000_flag_bits(void *contextId, s32 contextData, SpriteFrameState *object);

/* reset_indexed_flag_install_handlers.c */
void reset_indexed_flag_install_handlers(void *object, void *context, void *input);

/* reset_menu_state.c */
void reset_menu_state(void *menu, void *update_arg, void *input);

/* reset_mother_event_global_state.c */
void reset_mother_event_global_state(void *object);

/* reset_object_flag_and_set_countdown.c */
void reset_object_flag_and_set_countdown_400(struct S_800CEDA4_0 *object);

/* reset_object_substate_and_flag.c */
void reset_object_substate_and_flag(void *context, void *unused, struct SpriteFrameState *stateWords);

/* reset_reaction_global_flag_and_angle.c */
void reset_reaction_global_flag_and_angle(struct S_800CA7D8_0 *object);

/* run_object_handlers_supplied_state.c */
void run_object_handlers_supplied_state(s32 object, s32 state, s32 context);

/* set_actor_flag_copy_global.c */
void set_actor_flag_copy_global(void *actor, void *unused, struct SpriteFrameState *state);

/* set_flag_object_direction_c.c */
void set_flag_object_direction_12_c(struct S_800CCF18_0 *state);

/* set_person_status_and_code.c */
void set_person_status_and_code(struct S_800AAE00_1 *context, struct S_800AAE00_0 *status);

/* switch_actor_state.c */
void switch_actor_state(Rec_func_80094268_arg0 *actor, s32 unused, void *state_context);

/* tick_counter_and_enter_state_three.c */
void tick_counter_and_enter_state_three(Rec_func_80094268_arg0 *object, void *context_a, void *context_b, s32 check_arg);

/* update_object_state_and_lookup.c */
void update_object_state_and_lookup(Rec_func_80094268_arg0 *object, void *lookup_key, void *state_value);

/* update_person_global_state.c */
void update_person_global_state(void *object, s32 call_arg, s32 *values);

#endif

#ifndef TOWN_PERSON_STATE_H
#define TOWN_PERSON_STATE_H
struct SpriteFrameState;
/* Prototypes of the functions defined in src/town/person/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct TownObjectRecord;
struct ReactionState;
struct S_800AAE00_0;
struct S_800AAE00_1;
struct S_800CA458_0;
struct S_800CA7D8_0;
struct S_800CCC34_0;
struct S_800CEDA4_0;
struct SpriteFrameState;

/* adjust_two_state_values.c */
void drift_act_yoda_until_expiry(TownObjectRecord *object, ObjectPosition *state);

/* step_heading_turn_sequence.c */
void step_heading_turn_sequence(TownObjectRecord *sequence);

/* drift_act_niko_until_expiry.c */
void drift_act_niko_until_expiry(TownObjectRecord *object, struct S_800CA458_0 *state);

/* run_handler_and_enter_state_four.c */
void run_handler_and_enter_state_four(TownObjectRecord *object, s32 context, s32 update_data);

/* set_flag_object_heading_zero.c */
void set_flag_object_heading_zero(TownObjectRecord *state);

/* clear_record_indexed_flag.c */
void clear_record_indexed_flag(TownObjectRecord *state, s32 unused_context, void *unused_state_context);

/* dispatch_status_triggered_handler.c */
void dispatch_status_triggered_handler(s32 object, s32 unused, SpriteFlagsView *status);

/* dispatch_status_triggered_update.c */
void dispatch_status_triggered_update(TownObjectRecord *handler_arg, void *context, SpriteFlagsView *status);

/* forward_flag_state_update.c */
void forward_flag_state_update(TownObjectRecord *object, ObjectPosition *context, void *update_data);

/* increment_flag_object_counter.c */
void increment_flag_object_counter(TownObjectRecord *object);

/* initialize_actor_clear_shared_flag.c */
void initialize_actor_clear_shared_flag(TownObjectRecord *actor, s32 unused, void *init_param);

/* initialize_actor_clear_table_flag.c */
void initialize_actor_clear_table_flag(TownObjectRecord *actor, s32 unused, void *init_param);

/* initialize_actor_reaction_and_fixed_state.c */
void func_800CDF00(TownObjectRecord *actor, struct ReactionState *state, SpriteFrameState *output);
void initialize_actor_reaction_and_fixed_state(TownObjectRecord *actor, struct ReactionState *state, SpriteFrameState *output);

/* initialize_actor_state_table.c */
void initialize_actor_state_table(TownObjectRecord *actor, s32 context, void *state_context);

/* initialize_entity_action_state.c */
void initialize_entity_action_state(TownObjectRecord *entity, s32 unused, void *init_value);

/* initialize_indexed_callback_state.c */
void initialize_indexed_callback_state(TownObjectRecord *object, s32 unused, void *initValue);

/* initialize_mother_event_object_state.c */
void initialize_mother_event_object_state(void *object, s32 unused, void *initializationArg);

/* initialize_object_assigns_state_data.c */
void initialize_object_assigns_state_data(TownObjectRecord *object, void *unusedArg, void *initializationArg);

/* initialize_person_state.c */
void initialize_person_state(void *state, void *output);

/* initialize_reaction_object_and_clear_flag.c */
void initialize_reaction_object_and_clear_flag(TownObjectRecord *object, s32 unused, void *context);

/* install_object_handler_and_clear_slot_flag.c */
void install_object_handler_and_clear_slot_flag(void *object);

/* install_update_after_flag_clear.c */
void install_update_after_flag_clear(struct TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);

/* invoke_flag_state_callback.c */
void invoke_flag_state_callback(struct S_800CCC34_0 *object, s32 context, void *motion);

/* invoke_state_indexed_callback.c */
void invoke_state_indexed_callback(void *object, void *context, void *motion);

/* process_object_flag_bits.c */
void reset_object_entries_on_flag_bits(TownObjectRecord *contextId, s32 contextData, SpriteFrameState *object);

/* reset_indexed_flag_install_handlers.c */
void reset_indexed_flag_install_handlers(void *object, void *context, struct SpriteFrameState *input);

/* reset_menu_state.c */
void reset_menu_state(TownObjectRecord *menu, ObjectPosition *update_arg, SpriteFrameState *input);

/* reset_mother_event_global_state.c */
void reset_mother_event_global_state(void *object);

/* reset_object_flag_and_set_countdown.c */
void reset_person_slot_flag_and_angle(struct S_800CEDA4_0 *object);

/* initialize_scene_slot_39.c */
void initialize_scene_slot_39(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

/* reset_reaction_global_flag_and_angle.c */
void reset_reaction_global_flag_and_angle(struct S_800CA7D8_0 *object);

/* run_object_handlers_supplied_state.c */
void run_object_handlers_supplied_state(s32 object, ObjectPosition *position, s32 context);

/* set_actor_flag_copy_global.c */
void set_actor_flag_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state);

/* set_flag_object_direction_c.c */
void set_flag_object_heading_three_quarter_turn(TownObjectRecord *state);

/* set_person_status_and_code.c */
void set_person_status_and_code(struct S_800AAE00_1 *context, struct S_800AAE00_0 *status);

/* switch_actor_state.c */
void switch_actor_state(TownObjectRecord *actor, s32 unused, void *state_context);

/* tick_counter_and_enter_state_three.c */
void tick_counter_and_enter_state_three(TownObjectRecord *object, void *context_a, void *context_b, s32 check_arg);

/* update_object_state_and_lookup.c */
void update_object_state_and_lookup(TownObjectRecord *object, void *lookup_key, void *state_value);

/* update_person_global_state.c */
void update_person_global_state(void *object, s32 call_arg, s32 *values);

#endif

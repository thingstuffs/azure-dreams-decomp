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
struct S_800CA458_0;
struct SpriteFrameState;

/* initialize_two_value_adjustment_action.c */
void drift_act_yoda_until_expiry(TownObjectRecord *object, ObjectPosition *state);

/* step_heading_turn_sequence.c */
void step_heading_turn_sequence(TownObjectRecord *sequence);

/* drift_act_niko_until_expiry.c */
void drift_act_niko_until_expiry(TownObjectRecord *object, struct S_800CA458_0 *state);

/* run_handler_and_enter_state_four.c */
void run_handler_and_enter_state_four(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* set_flag_object_heading_zero.c */
void set_flag_object_heading_zero(TownObjectRecord *state);

/* clear_record_indexed_flag.c */
void clear_record_indexed_flag(TownObjectRecord *state, ObjectPosition *unused_position, SpriteFrameState *unused_sprite);

/* dispatch_status_triggered_handler.c */
void dispatch_status_triggered_handler(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *status);

/* dispatch_status_triggered_update.c */
void dispatch_status_triggered_update(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *status);

/* forward_flag_state_update.c */
void forward_flag_state_update(TownObjectRecord *object, ObjectPosition *context, void *update_data);

/* increment_flag_object_counter.c */
void increment_flag_object_counter(TownObjectRecord *object);

/* initialize_actor_clear_shared_flag.c */
void initialize_actor_clear_shared_flag(TownObjectRecord *actor, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* initialize_actor_clear_table_flag.c */
void initialize_actor_clear_table_flag(TownObjectRecord *actor, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* initialize_actor_reaction_and_fixed_state.c */
void initialize_actor_reaction_and_fixed_state(TownObjectRecord *actor, struct ObjectPosition *state, SpriteFrameState *output);

/* initialize_actor_state_table.c */
void initialize_actor_state_table(TownObjectRecord *actor, ObjectPosition *position, SpriteFrameState *sprite);

/* initialize_entity_action_state.c */
void initialize_entity_action_state(TownObjectRecord *entity, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* initialize_indexed_callback_state.c */
void initialize_indexed_callback_state(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* initialize_mother_event_object_state.c */
void initialize_mother_event_object_state(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* initialize_object_assigns_state_data.c */
void initialize_object_assigns_state_data(TownObjectRecord *object, ObjectPosition *unusedArg, SpriteFrameState *initializationArg);

/* initialize_person_state.c */
void initialize_person_state(TownObjectRecord *state, ObjectPosition *position);

/* initialize_reaction_object_and_clear_flag.c */
void initialize_reaction_object_and_clear_flag(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* install_object_handler_and_clear_slot_flag.c */
void install_object_handler_and_clear_slot_flag(TownObjectRecord *object);

/* install_update_after_flag_clear.c */
void install_update_after_flag_clear(struct TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);

/* invoke_flag_state_callback.c */
void invoke_flag_state_callback(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* invoke_state_indexed_callback.c */
void invoke_state_indexed_callback(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* process_object_flag_bits.c */
void reset_object_entries_on_flag_bits(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* reset_indexed_flag_install_handlers.c */
void reset_indexed_flag_install_handlers(TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *input);

/* reset_menu_state.c */
void reset_menu_state(TownObjectRecord *menu, ObjectPosition *update_arg, SpriteFrameState *input);

/* reset_mother_event_global_state.c */
void reset_mother_event_global_state(TownObjectRecord *object);

/* reset_object_flag_and_set_countdown.c */
void reset_person_slot_flag_and_angle(TownObjectRecord *object);

/* initialize_scene_slot_39.c */
void initialize_scene_slot_39(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

/* reset_reaction_global_flag_and_angle.c */
void reset_reaction_global_flag_and_angle(TownObjectRecord *object);

/* run_object_handlers_supplied_state.c */
void run_object_handlers_supplied_state(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* set_actor_flag_copy_global.c */
void set_actor_flag_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state);

/* set_flag_object_direction_c.c */
void set_flag_object_heading_three_quarter_turn(TownObjectRecord *state);

/* set_person_status_and_code.c */
void set_person_status_and_code(TownObjectRecord *context, struct S_800AAE00_0 *status);

/* switch_actor_state.c */
void switch_actor_state(TownObjectRecord *actor, ObjectPosition *unused_position, SpriteFrameState *sprite);

/* tick_counter_and_enter_state_three.c */
void tick_counter_and_enter_state_three(TownObjectRecord *object, void *context_a, void *context_b, s32 check_arg);

/* update_object_state_and_lookup.c */
void update_object_state_and_lookup(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* update_person_global_state.c */
void update_person_global_state(void *object, s32 call_arg, s32 *values);

void step_heading_turn_sequence_reversed(TownObjectRecord *sequence);

#endif

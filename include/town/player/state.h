#ifndef TOWN_PLAYER_STATE_H
#define TOWN_PLAYER_STATE_H
/* Prototypes of the functions defined in src/town/player/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/position_views.h"

struct EntityRec;
struct TownObjectRecord;
struct S_800946FC_0;
struct S_80098C04_0;

/* advance_player_state.c */
void advance_player_state(struct TownObjectRecord *context, EntityRec *state, SpriteFrameState *updateData);

/* clear_script_flag_bit.c */
void clear_script_flag_bit(s32 bit_index);

/* clear_shared_flag_and_initialize_object.c */
void clear_shared_flag_and_initialize_object(void *state, void *context, void *mode);

/* sync_collision_motion_y.c */
void sync_collision_motion_y(ObjectPosition *source);

/* dispatch_sound_by_global_flag.c */
void dispatch_sound_by_global_flag(void);

/* ease_object_value_and_advance_state.c */
void ease_object_value_and_advance_state(UnsignedCountdownView *state, ObjectPosition *object);

/* forward_state_value_to_handler_a.c */
void forward_state_value_to_handler_a(void *state, ObjectPosition *value);

/* forward_state_value_to_handler_b.c */
void forward_state_value_to_handler_b(void *state, ObjectPosition *value);

/* get_script_flag_mask.c */
s32 get_script_flag_mask(s32 flagIndex);

/* initialize_actor_action_state.c */
void initialize_actor_action_state(TownObjectRecord *object, ObjectPosition *state, s32 initData);

/* initialize_actor_interaction_state.c */
void install_actor_interaction_handler(struct S_800946FC_0 *object);

/* initialize_mode_state_tables.c */
void initialize_mode_state_tables(void);

/* initialize_player_slot_state.c */
void initialize_player_slot_state(TownObjectRecord *record, void *ptr, void *ptr2);

/* initialize_record_and_clear_shared_flag.c */
void initialize_record_and_clear_shared_flag(TownObjectRecord *primary_value, ObjectPosition *secondary_value, void *context_value);

/* initialize_state_from_terminated_entries.c */
void initialize_state_from_terminated_entries(s32 *entries);

/* read_script_flag_range.c */
s32 read_script_flag_range(s32 start_index, s32 count);

/* reset_player_slot_state.c */
void reset_player_slot_state(TownObjectRecord *object, void *ptr, void *ptr2);

/* run_action_with_flag_fallback.c */

/* run_the_action_sequence_context_unless_flag_a_set.c */
s32 create_item_menu_unless_minigame(s32 context);

/* select_next_item_state.c */
void select_next_item_state(void *object, void *position, void *context);

/* set_handler_counter_and_clear_flag.c */
void set_handler_counter_and_clear_flag(struct S_80098C04_0 *state, ObjectPosition *target);

/* set_script_flag_bit.c */
void set_script_flag_bit(s32 bit_index);

/* set_state_bytes_from_flags.c */
void set_state_bytes_from_flags(s32 flags, u8 *state);

/* stop_scene_player_and_defer_action_setup.c */
void stop_scene_player_and_defer_action_setup(void);

/* update_actor_action_state.c */
void update_actor_action_state(TownObjectRecord *state, ObjectPosition *motion, s32 callback_arg);

/* update_actor_and_dispatch_state.c */
void update_actor_and_dispatch_state(void *actor, ObjectPosition *record, s32 context);

/* update_actor_with_interaction_state.c */
void update_actor_with_interaction_state(TownObjectRecord *controller, ObjectPosition *entity, SpriteFrameState *context);

/* update_entity_and_dispatch_timed_state.c */
void update_entity_and_dispatch_timed_state(void *state, void *entity, void *transition_arg);

/* write_script_flag_range.c */
void write_script_flag_range(s32 base, s32 bits, s32 count);

void run_action_with_flag_fallback(s32 *value, ObjectPosition *context, SpriteFrameState *sprite);


#endif

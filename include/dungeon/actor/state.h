#ifndef DUNGEON_ACTOR_STATE_H
#define DUNGEON_ACTOR_STATE_H

/* Function contracts owned by src/dungeon/actor/state/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"

struct SpriteFrameState;
struct ActorRecord;
void create_default_state_object(s16 new_state);
void set_actor_action_state_eight(void *record_data, void *unused_position, void *unused_context);

struct ObjectPosition;
struct S_800D491C_0;
void set_actor_data_pointer(struct S_800D491C_0 *object, s32 context, void *source, void *target);

s32 propagate_actor_action_flag(struct ActorRecord *body, struct ObjectPosition *position, struct SpriteFrameState *sprite, struct ActorRecord *actor);
void install_trap_handler_after_action_flag_propagation(void *owner, s32 context, s32 sprite, s32 *record);


void roll_actor_flag_once(ActorRecord *body, s32 divisor);

void initialize_action_state_29(void *state, s32 unused_context, struct SpriteFrameState *unused_sprite, struct ActorRecord *unused_actor);

void reset_record_to_state_34(void *state, void *unused_context, struct SpriteFrameState *unused_sprite, struct ActorRecord *unused_actor);

struct ObjectPosition;
struct SpriteFrameState;

void refresh_actor_proximity_state(struct ActorRecord *context);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 try_apply_confusion_status(void *ptr, s32 threshold_input, s32 kind_input);

void *merge_creature_abilities_and_state(void *first, void *second, void *destination);
s32 try_apply_status_effect(void *target, s16 chance, s16 duration);

struct Actor;
s32 check_global_or_linked_flag_20000(struct Actor *actor);

#include "shared/sprite_frame_state.h"
s16 relink_entity_and_clear_high_flag(void *context, void *position, void *entity, s16 near_range, s16 far_range, s8 *state_out_addr);
s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);

#endif

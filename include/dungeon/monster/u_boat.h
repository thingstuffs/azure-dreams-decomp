#ifndef DUNGEON_MONSTER_U_BOAT_H
#define DUNGEON_MONSTER_U_BOAT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 uboat_behavior_entry[];

/* Facing, countdown, and reference position for the spawned item-action effect. */
typedef struct AdvanceActorItemActionBody {
    u8 pad_00[0x2A];
    s16 facing_angle;
    u8 pad_2C[0x68];
    s16 direction_index;
    u16 ticks_remaining;
    u8 pad_98[0x14];
    void *reference_position;
} AdvanceActorItemActionBody;

/* Phase, fade timer, and source link for U-Boat's two rotating aura effects. */
typedef struct UBoatAuraEffectBody {
    u8 pad_00[0x2C];
    union { s16 s; u16 u; } phase;
    u8 pad_2E[0x8];
    union { u16 s; s16 u; } ticks;
    s16 duration;
    u8 pad_3A[0x6];
    ActorRecord *owner;
    union { ObjectPosition *position; u32 *words; } source;
} UBoatAuraEffectBody;



void advance_actor_action(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

void leave_actor_aura_mode(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);
void update_actor_timed_tile_motion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_staged_actor_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *record, ActorRecord *actor);
void enter_actor_aura_mode(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_visual_motion(ActorRecord *body, ObjectPosition *motion_arg, SpriteFrameState *sprite);
void update_rotating_actor_aura(UBoatAuraEffectBody *effect, ObjectPosition *position, SpriteFrameState *visual);
void update_shrinking_sprite_effect(UBoatAuraEffectBody *effect, void *output, void *render_data);

void update_actor_movement_state(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor_arg);

void choose_and_execute_actor_step(ActorRecord *work_data, ObjectPosition *action_context, SpriteFrameState *position, ActorRecord *actor);

void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);
void update_actor_turn_and_action(ActorRecord *entity, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_800A9E70_arg0.h"
s32 try_turn_actor_toward_target(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *target, ActorRecord *actor);

void update_actor_action_transition(ActorRecord *state, ObjectPosition *update_mode, SpriteFrameState *sprite, ActorRecord *entity);
void update_actor_movement_history(ActorRecord *motion, ObjectPosition *position, SpriteFrameState *record, ActorRecord *object);

void begin_actor_action(ActorRecord *state, ObjectPosition *world_pos, SpriteFrameState *sprite, ActorRecord *actor);
void begin_actor_exclusive_action(ActorRecord *entity, ObjectPosition *unused_1, SpriteFrameState *unused_sprite, s32 unused_3, s32 requested_mode);
void prepare_actor_directional_action(ActorRecord *entity, ObjectPosition *action_param, SpriteFrameState *action_sprite, u8 *frame_table, s32 fallback_state);

#endif

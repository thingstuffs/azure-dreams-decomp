#ifndef DUNGEON_MONSTER_DEATH_H
#define DUNGEON_MONSTER_DEATH_H

/* Function contracts owned by src/dungeon/monster/death/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
/* Body of the 0x211 node created by create_parent_return_effect. */
typedef struct ParentReturnEffectBody {
    union {
        s32 packed;
        struct { u8 red, green, blue, unk_03; } channels;
    } base_color;
    union {
        s32 packed;
        struct { s8 red, green, blue; u8 unk_07; } channels;
    } color;
    s32 output_color;
    u8 unk_0C[0x8];
    s16 unk_14;
    u8 unk_16[0x1C];
    s16 fade_level;
    u8 unk_34[0x2];
    union { s16 s; u16 u; } target_x;
    union { s16 s; u16 u; } target_y;
    u16 target_z;
    u8 unk_3C[0x4];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 acceleration_x;
    s32 acceleration_y;
    s32 acceleration_z;
} ParentReturnEffectBody;

void update_entity_movement_animation_and_ground(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite);








void advance_effect_toward_target(ParentReturnEffectBody *effect, ObjectPosition *position);
void finish_staged_jump_at_tile_center(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_actor_states_and_entity_flags(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity);

struct S_80173C40_0;
void initialize_object_and_clear_state(struct S_80173C40_0 *object, ObjectPosition *position, SpriteFrameState *init_context, ActorRecord *actor);

/* Directional frame entries; the full allocation extent is not inferred. */
extern u8 death_frame_set[];

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void create_parent_return_effect(void *parent_obj, s16 effect_param, s32 initial_value, s16 duration, s16 offset_x, s16 offset_y, s16 offset_z);
void spawn_parent_offset_random_motion_effect(void *parent_arg, register s16 effect_param_arg, register s32 state_value_arg, register s32 unused_arg, register s32 offset_x_arg, register s32 offset_y_arg, register s32 offset_z_arg);

void advance_entity_path_state(ActorRecord *motion_state, ObjectPosition *unused, SpriteFrameState *entity, ActorRecord *path_state);
void apply_conditional_actor_effect(ActorRecord *action_state, ObjectPosition *effect_context, SpriteFrameState *action_context, ActorRecord *actor);
s32 attempt_target_action(ActorRecord *action_state, ObjectPosition *effect_arg, SpriteFrameState *target, ActorRecord *actor);
void dispatch_actor_animation_and_action(ActorRecord *motion_in, ObjectPosition *context_in, SpriteFrameState *entity_in, ActorRecord *actor_in);

#endif

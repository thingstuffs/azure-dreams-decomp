#ifndef DUNGEON_MONSTER_BALOON_H
#define DUNGEON_MONSTER_BALOON_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"




void advance_actor_hop_animation(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);



void advance_actor_animation_and_fall(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_approach_descent_return(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_monster_staged_motion(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor_ptr);

void update_actor_turn_behavior(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

typedef struct {
    u8 pad_00[2];
    u16 x;
    u8 pad_04[2];
    u16 y;
    u8 pad_08[2];
    u16 z;
    u8 pad_0C[0xA];
    u16 height;
} BaloonTemplateAnchor;

typedef struct {
    u8 pad_00[0x2A];
    s16 facing;
} BaloonTemplateFacing;

/* Directional template constructor used by the Baloon rise effect. */
void create_directional_template_effect(void *unused, BaloonTemplateAnchor *anchor,
    SpriteFrameState *object_template, BaloonTemplateFacing *facing_source);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void spawn_angled_random_velocity_effect(EntityRec *source, u32 angle, s32 effect_param);

/* Timer and fade divisor for a directional random-velocity effect. */
typedef struct DirectionalRandomVelocityEffectBody {
    u8 pad_00[0xA];
    u16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} DirectionalRandomVelocityEffectBody;

/* Motion, terrain-collision state, and lifetime for an origin-relative effect. */
typedef struct OriginMotionEffectBody {
    u8 pad_00[0x2];
    s16 state;
    u8 pad_04[0x8];
    union { s16 s; u16 u; } lifetime;
    s16 lifetime_divisor;
    u8 pad_10[0x8];
    u16 animation_counter;
    u8 pad_1A[0x12];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 acceleration_x;
    s32 acceleration_y;
    s32 acceleration_z;
} OriginMotionEffectBody;



void update_effect_collision_and_lifetime(OriginMotionEffectBody *effect,
    ObjectPosition *position, SpriteFrameState *visual);

void initialize_angle_indexed_target(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *target, ActorRecord *angleSource);
s32 random_below_limit(s32 limit);

void relocate_entity_after_animation(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, void *object);

void advance_baloon_along_path(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void clear_high_flag_and_update_counter(ActorRecord *body, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *actor);
s32 initialize_directional_object(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_counter_and_status(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *unused, ActorRecord *actor);

#endif

#ifndef DUNGEON_MONSTER_BLUME_H
#define DUNGEON_MONSTER_BLUME_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 blume_direction_frames[];
extern u8 blume_direction_frames_2[];



typedef struct DirectionalParticlesAndResetActorBody {
    u8 pad_00[0x96];
    u16 lifetime;
    u16 hit_state;
    u8 pad_9A[1];
    u8 unk_9B;
    u8 pad_9C[2];
    u16 unk_9E;
    u8 pad_A0[4];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 acceleration_z;
} DirectionalParticlesAndResetActorBody;

typedef struct GrowingCollidingEffectBody {
    s16 unk_00;
    u8 pad_02[0x18];
    s16 unk_1A;
    u8 pad_1C[0x8];
    u16 unk_24;
    u16 unk_26;
    u8 pad_28[0x38];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
    s32 unk_74;
} GrowingCollidingEffectBody;

void update_damped_height_effect(DirectionalParticlesAndResetActorBody *state, ObjectPosition *position, SpriteFrameState *object);
void update_growing_colliding_effect(GrowingCollidingEffectBody *effect, ObjectPosition *position, SpriteFrameState *sprite);

/* Callback entry points. */
struct BlumeFadingMotionBody;
void update_fading_motion_effect(struct BlumeFadingMotionBody *effect, ObjectPosition *transform, SpriteFrameState *color);

void advance_actor_staged_animation(ActorRecord *action_data, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct T_80170874_S_80DB9000_1;
struct T_80170874_S_80DB9000_2;
struct T_80170874_S_80DB9000_3;
void project_sprite_entries_to_quads(struct T_80170874_S_80DB9000_1 *sprite_size, struct T_80170874_S_80DB9000_2 *position, struct T_80170874_S_80DB9000_3 *sprite, s16 depth_bias);

void cast_blume_targeted_spell(ActorRecord *controller, ObjectPosition *motion, SpriteFrameState *action_sprite, ActorRecord *actor_body);
void begin_actor_directional_target_action(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
void *spawn_blume_actor(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c);
void dispatch_blume_actions(ActorRecord *actor_in, ObjectPosition *actor_data_in, SpriteFrameState *sprite_in, ActorRecord *status_in);

#endif

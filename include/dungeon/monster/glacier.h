#ifndef DUNGEON_MONSTER_GLACIER_H
#define DUNGEON_MONSTER_GLACIER_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Body of the 0x212 particles created during Glacier's forward-tile action. */
typedef struct CollidingSpriteParticleBody {
    u8 unk_00[0x14];
    s16 contacted_ground;
    u8 unk_16[0x8];
    union { s16 s; u16 u; } remaining;
    u16 animation_tick;
    u8 unk_22[0x2E];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 acceleration_x;
    s32 acceleration_y;
    s32 acceleration_z;
} CollidingSpriteParticleBody;

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 glacier_direction_frames[];




void update_staged_item_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *target, ActorRecord *actor);



void update_action_and_check_forward_tile(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *entity);



void update_item_hop_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void update_actor_timed_effects(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg);

/* Callback entry points. */
struct DirectionalEffectBody;
void advance_item_motion_collision(struct DirectionalEffectBody *motion, void *position, SpriteFrameState *update_arg);
void update_monster_appearance_motion(ActorRecord *entity_arg, void *motion_arg, SpriteFrameState *monster_arg);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void advance_selected_item_action_2(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

#include "records/Rec_func_801744DC_arg0.h"
#include "records/Rec_func_801744DC_arg1.h"
void initialize_item_sprite_frame(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void spawn_directional_effect(Rec_func_801744DC_arg0 *source, Rec_func_801744DC_arg1 *origin, void *unused);
void spawn_directional_particle(Rec_func_801744DC_arg0 *source, Rec_func_801744DC_arg1 *origin, void *unused_sprite);

void *find_nearby_eligible_entry(u8 *current, s32 wanted_24, s32 wanted_25, s32 height_center);

void grow_terrain_colliding_sprite(CollidingSpriteParticleBody *effect, ObjectPosition *position, SpriteFrameState *sprite);

#endif

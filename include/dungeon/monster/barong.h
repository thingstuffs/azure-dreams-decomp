#ifndef DUNGEON_MONSTER_BARONG_H
#define DUNGEON_MONSTER_BARONG_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef struct {
    u8 index;
    u8 group;
    u8 param;
    u8 flags;
} BarongItemDescriptor;

/* Motion payload of Barong's tossed item node (allocation flags 0x12).
 * The initializer and terrain updater agree on the direction, item bytes,
 * tile coordinates, velocity and vertical acceleration. This is the observed
 * 0x6C-byte body prefix; position and sprite remain separate node records. */
typedef struct TossedItemMotionBody {
    u8 unk_00[0x1C];
    union { s16 s; u16 u; } phase;
    union { s16 s; u16 u; } settle_started;
    u8 unk_20[4];
    union { s16 s; u16 u; } direction;
    union { u16 u; s16 s; } settle_frames;
    u8 unk_28[4];
    BarongItemDescriptor arg;
    u8 unk_30[4];
    void *owner;
    u8 unk_38[0x18];
    union { s8 s; u8 u; } cell_x;
    union { s8 s; u8 u; } cell_y;
    u8 unk_52[2];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 acceleration_x;
    s32 acceleration_y;
    s32 acceleration_z;
} TossedItemMotionBody;

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 barong_direction_frames[];







void update_actor_movement_animation_states_completes_timed_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void update_motion_and_grow_sprite(void *motion, void *position, SpriteFrameState *sprite);





void advance_timed_actor_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_arcing_actor_move(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void hop_actor_and_restore_scale(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_hop_action(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_hop_motion_and_completion(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_tile_centering_motion_animation_restores_actor_timer_expires(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_timed_hop_and_landing(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* Callback entry points. */
struct S_801747F0_1;
void update_motion_and_terrain_collision(TossedItemMotionBody *motion, struct S_801747F0_1 *position, void *object);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void start_direction_based_action(ActorRecord *body, ObjectPosition *unused, SpriteFrameState *animation, ActorRecord *actor);

void reset_actor_after_timed_movement(ActorRecord *action_arg, ObjectPosition *motion_arg, SpriteFrameState *sprite_arg, ActorRecord *entity_arg);

void advance_deforming_action_animation(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite_in, ActorRecord *actor_in);

#endif

#ifndef DUNGEON_ACTOR_MOTION_H
#define DUNGEON_ACTOR_MOTION_H

#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"



void begin_pushed_actor_move(void *state, void *unused, void *position, void *actor);
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void dispatch_actor_action_2(u8 *actor, void *action_arg, void *action_data, u8 *state);

void update_airborne_actor_motion(void *action, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *actor);

struct ActorHopState;
struct ActorHopMotion;
struct ActorHopParams;
struct ActorHopExtra;
s32 update_actor_hop_and_grow(struct ActorHopState *state, struct ActorHopMotion *motion, struct ActorHopParams *params, struct ActorHopExtra *extra);



void update_actor_facing_and_lifecycle(void *state, ObjectPosition *motion, SpriteFrameState *part);
void update_rising_landing_effect(void *effect, ObjectPosition *motion, SpriteFrameState *sprite);

struct S_800AC480_0;
struct S_800AC480_3;
s32 interpolate_actor_to_terrain_tile(struct S_800AC480_0 *state, ObjectPosition *motion, MovingTile *tile, struct S_800AC480_3 *height);
void run_terrain_tile_interpolation(void *owner, ObjectPosition *motion, MovingTile *tile, void *height);

struct CallbackOwner;
struct Rec_func_800A9E70_arg0;
struct Rec_D_80082E80;
s32 update_actor_transform_from_parent(struct Rec_func_800A9E70_arg0 *state, ObjectPosition *position, struct Rec_D_80082E80 *tile, void *actor);
void install_actor_action_handler_after_floor_trap_check(struct CallbackOwner *owner, ObjectPosition *position, void *tile, ActorRecord *actor);

s32 update_thrown_actor_travel(void *state, ObjectPosition *position, SpriteFrameState *tile, ActorRecord *actor);
void install_actor_action_handler_after_thrown_travel(struct CallbackOwner *owner, ObjectPosition *position, void *tile, ActorRecord *actor);

s32 update_actor_hop_and_shrink(void *animation, void *motion, SpriteFrameState *scale, void *render);

s32 update_actor_movement_to_tile(void *move_state, void *motion, void *target_tile, ActorRecord *actor);
struct S_800D9884_0;
void update_actor_target_after_check(struct S_800D9884_0 *state, void *motion, void *source, void *target);
void advance_actor_movement_to_tile(void *entity_ptr, void *input_arg_1, void *input_arg_2, void *actor_ptr);


/* The trail callbacks keep seven 8-byte samples at work +0x24. Their motion
 * and brightness arithmetic reads the same halves signed and unsigned; the
 * views below preserve those access widths without recasting each access. */
typedef union TrailHalf { s16 s; u16 u; u8 byte; } TrailHalf;
typedef union TrailCoord {
    s32 value;
    struct { u16 fraction; TrailHalf whole; } parts;
} TrailCoord;
typedef struct TrailVector { TrailCoord x, y, z; } TrailVector;
typedef struct TrailMotion { TrailVector position, velocity; } TrailMotion;
typedef struct TrailPoint { TrailHalf x, y, z; u16 pad; } TrailPoint;
typedef struct ActorTrailWork {
    /* 0x00 */ TrailMotion *target;
    /* 0x04 */ ActorRecord *owner;
    /* 0x08 */ ObjectNodeHeader *follow;
    /* 0x0C */ TrailVector position;
    /* 0x18 */ TrailVector previous;
    /* 0x24 */ TrailPoint history[7];
    u8 pad_5C[8];
    /* 0x64 */ TrailHalf state, timer;
    /* 0x68 */ u16 ticks;
    /* 0x6A */ TrailHalf brightness;
    u8 pad_6C[2];
    /* 0x6E */ TrailHalf shade_offset;
} ActorTrailWork;

void update_position_history_and_shading(ActorTrailWork *obj, TrailMotion *coords_out, SpriteFrameState *rgb);

void handle_actor_commands_and_facing(void *actor, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor_data);

#endif

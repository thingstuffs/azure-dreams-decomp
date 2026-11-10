#ifndef DUNGEON_MONSTER_WEADOG_H
#define DUNGEON_MONSTER_WEADOG_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef struct GridPoint {
    s16 x;
    s16 y;
} GridPoint;

/* The 0x12 node installed by spawn_moving_actor and advanced by the flight callback. */
typedef struct WeadogFlightBody {
    u8 pad_00[0x2C];
    s16 phase;
    s16 phase_timer;
    u8 pad_30[4];
    s16 direction;
    s16 travel_frames;
    u8 pad_38[8];
    ActorRecord *owner;
    u8 pad_44[0x18];
    s8 spawner_tile_x;
    s8 spawner_tile_y;
    u8 pad_5E[0x0E];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 acceleration_x;
    s32 acceleration_y;
    s32 gravity;
} WeadogFlightBody;



void advance_timed_actor_hop(void *action, void *motion, SpriteFrameState *sprite, void *actor);
void advance_timed_hop_and_recover(ActorRecord *motion_state, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_weadog_timed_move(void *action, void *motion, SpriteFrameState *sprite, void *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void advance_timed_sprite_flashing_sequence(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void *create_overlay_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c);
void create_random_color_offset_effect(void *parent_arg, s16 initial_14, s32 unused, s16 initial_32, s16 offset_x, s16 offset_y, s16 offset_z);
void update_actor_targeted_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);


/* Flight callback contracts; their private records are defined by the updater TUs. */
struct S_func_80EDF000_1;
struct S_func_80EDF000_2;
struct S_func_80EF1000_1;
struct S_func_80EF1000_2;
struct S_func_80EF1000_3;
struct S_func_80EF7000_1;
struct S_func_80EF7000_2;
struct S_func_80EF7000_3;
void update_flight_landing_and_fall(struct S_func_80EF1000_1 *motion, struct S_func_80EF1000_2 *position, struct S_func_80EF1000_3 *sprite);
void advance_motion_through_landing_and_fall(struct S_func_80EF7000_1 *motion, struct S_func_80EF7000_2 *position, struct S_func_80EF7000_3 *animation);
void advance_item_flight_to_floor(struct WeadogFlightBody *motion, struct S_func_80EDF000_1 *position, struct S_func_80EDF000_2 *render);

#endif

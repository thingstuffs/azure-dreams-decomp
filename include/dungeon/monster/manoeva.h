#ifndef DUNGEON_MONSTER_MANOEVA_H
#define DUNGEON_MONSTER_MANOEVA_H
struct ActorRecord;

/* Function contracts owned by src/dungeon/monster/manoeva/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/object_node.h"

/* Body allocated by create_terrain_scaled_actor_effect with flags 0x100.
 * Its update and depth-sliced draw callbacks share these scale and phase slots. */
typedef struct ManoevaTerrainEffectBody {
    s16 *owner_facing;
    u8 *owner_action;
    u16 *owner_action_flags;
    ObjectNodeHeader *owner_node;
    u8 pad_10[4];
    SpriteFrameState *owner_sprite;
    ObjectPosition *owner_position;
    union { s16 s; u16 u; } base_scale;
    s16 expanding;
    union { s16 s; u16 u; } wobble_phase;
    s16 corner0_scale_x;
    s16 corner0_scale_y;
    s16 corner1_scale_x;
    s16 corner1_scale_y;
    s16 corner2_scale_x;
    s16 corner2_scale_y;
    s16 corner3_scale_x;
    s16 corner3_scale_y;
} ManoevaTerrainEffectBody;

/* Actor-state dispatch; the final argument is reserved by the caller ABI. */
s32 dispatch_actor_action_state(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, s32 unused_force_state);
typedef struct ManoevaParticleBurstBody {
    u8 pad_00[0x20];
    union { s16 s; u16 u; } lifetime;
} ManoevaParticleBurstBody;
/* Lifetime, direction, and anchor fields for the timed Noise visual node. */
typedef struct TimedActorVisualEffectBody {
    u8 pad_00[0x94];
    s16 direction;
    union { s16 s; u16 u; } ticks_remaining;
    u8 pad_98[0x6];
    s16 secondary_ticks;
    u8 pad_A0[0x2];
    s16 use_linked_position;
    u8 pad_A4[0x4];
    void *reference_position;
} TimedActorVisualEffectBody;
void advance_actor_turn_path(ActorRecord *move_data_in, ObjectPosition *context, SpriteFrameState *tile_in, ActorRecord *actor_in);
void spawn_offset_motion_object(ActorRecord *parent_data, ObjectPosition *origin, SpriteFrameState *source_data, s16 position_index);
void update_manoeva_actor_callbacks_and_floor_motion();








void advance_actor_sprite_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void *spawn_manoeva(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height);

/* Callback entry points. */
void transfer_linked_object_state(ActorRecord *owner, ObjectPosition *object_id, SpriteFrameState *dest_object, ActorRecord *dest_state);
void update_manoeva_particle_burst(ManoevaParticleBurstBody *effect, s32 *motion, SpriteFrameState *color_data);

void create_terrain_scaled_actor_effect(ObjectNodeHeader *source, s16 *facing, u8 *action, u16 *flags);
void create_knockback_travel_object(ActorRecord *owner_data, ObjectPosition *position_arg, SpriteFrameState *source_arg, ActorRecord *context_arg);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void spawn_manoeva_particle_burst(ObjectPosition *origin, SpriteFrameState *source_sprite);

s32 draw_linked_record_chain(u8 *record_data, ObjectPosition *position, SpriteFrameState *sprite);

void update_actor_item_use_animation(ActorRecord *action, void *item, SpriteFrameState *sprite, ActorRecord *actor);

struct S_80173D78_2;
void update_actor_target_effect_action(ActorRecord *body, ObjectPosition *context, SpriteFrameState *sprite, struct S_80173D78_2 *actor);

void *spawn_manoeva_from_record(ActorRecord *body, ObjectPosition *unused1, SpriteFrameState *position, Rec_D_80082E80 *spawn_data);

void update_manoeva_behavior(ActorRecord *actor_state_in, ObjectPosition *update_context_in, SpriteFrameState *map_object, ActorRecord *actor_data);
void update_terrain_scaled_actor_effect(struct ManoevaTerrainEffectBody *effect, MovingPosition *out_position, SpriteFrameState *out_render);

#endif

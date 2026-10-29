#ifndef DUNGEON_ACTOR_POSITION_H
#define DUNGEON_ACTOR_POSITION_H
/* Prototypes of the functions defined in src/dungeon/actor/position/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_trail_views.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct ActorTrailWork;
struct S_800AC480_0;
struct S_800AC480_3;

/* advance_actor_movement_to_tile.c */
void advance_actor_movement_to_tile(void *entity_ptr, void *input_arg_1, void *input_arg_2, void *actor_ptr);

/* create_actor_at_tile.c */
void *create_actor_at_tile(s16 spawn_kind, u16 tile_x, u16 tile_y, s16 height);

/* create_actor_graphics_at_tile.c */
void *create_actor_graphics_at_tile(s16 object_kind, u16 tile_x, u16 tile_y, s16 height);

/* create_actor_sprite_at_tile.c */
void *create_actor_sprite_at_tile(s16 object_kind, u16 tile_x, u16 tile_y, s16 height);

/* create_actor_with_tile_flags.c */
void *create_actor_with_tile_flags(s16 variant, u16 tile_x, u16 tile_y, s16 spawn_height);

/* create_player_tile_actor_at_coordinates.c */
void *create_player_tile_actor_at_coordinates(u16 tile_x, u16 tile_z, u16 height);

/* interpolate_actor_to_terrain_tile.c */
s32 interpolate_actor_to_terrain_tile(struct S_800AC480_0 *move_state, ObjectPosition *motion, MovingTile *target_tile, struct S_800AC480_3 *height_state);

/* move_actor_to_destination_tile.c */
void move_actor_to_destination_tile(Rec_func_8008ACDC_arg0 *actor, ObjectPosition *motion, SpriteFrameState *destination, void *context);

/* update_actor_movement_to_tile.c */
s32 update_actor_movement_to_tile(void *move_state, void *motion, void *target_tile, ActorRecord *actor);

/* update_attached_effect_position.c */
void update_attached_effect_position(void *object, MovingPosition *position, void *anim_state);

/* update_position_history_and_shading.c */
void update_position_history_and_shading(struct ActorTrailWork *obj, TrailMotion *coords_out, SpriteFrameState *rgb);

#endif

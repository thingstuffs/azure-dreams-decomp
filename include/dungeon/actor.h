#ifndef DUNGEON_ACTOR_H
#define DUNGEON_ACTOR_H
#include "common.h"
#include "shared/dungeon_moving_views.h"
#include "shared/entity.h"
struct SpriteFrameState;
void reserve_tw_mon_load(s32 request);

void jyotyu_set_reserve_all(void);
void jyotyu_set_reserve_dngn(void);
void announce_familiar_defeat(void *input_data);
void begin_action_33_and_dispatch(void *object, s32 unused_1, s32 unused_2, s32 target);
s32 check_active_object_state_567(void);
s32 check_enabled_neighbor_height(s32 world_x, s32 world_y, s16 world_z, u32 direction, s32 disabled);
s32 check_entity_eligibility(void *entity);
s32 check_row_column_or_diagonal_alignment(MovingTile *source, MovingTile *target);
s32 check_tile_path_clear(void *source, void *target);
s32 choose_best_eligible_entry_for_actor(void *actor_arg, s32 action_arg, MovingTile *origin);
void copy_indexed_entry_data(void *entity);
void *find_eligible_nearby_entry(s32 x, s32 y, void *end, void *owner);
void rotate_actor_movement_queue(MovingTile *position, void *state);
void run_saved_actor_action(void *object, s32 unused, void *animation, void *actor);
void spawn_salam_particles(EntityRec *source, s16 effect_param, s32 render_param);
void update_actor_facing_animation(void *actor, EntityRec *motion, void *sprite, ActorRecord *status);
extern void update_actor_movement_and_map_flags(void *obj, s32 move_mode,struct SpriteFrameState *actor, void *map);
#endif

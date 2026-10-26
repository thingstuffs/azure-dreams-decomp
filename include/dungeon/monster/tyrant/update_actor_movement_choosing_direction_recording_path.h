#ifndef DUNGEON_OVL_7F0F7800_P03_H
#define DUNGEON_OVL_7F0F7800_P03_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))



extern s32 check_entity_relation();
extern void cycle_map_cell_flags();
extern void update_map_cell_flags_with_item_limit();
extern s32 check_diagonal_side_height();
extern s32 check_movement_clearance_and_height();
extern s32 test_neighbor_position_relation();
extern void * find_adjacent_actor();
extern void * probe_directional_neighbor();
extern u16 get_rounded_facing_and_rounding_flag();
extern void select_actor_route_target();
extern void update_actor_proximity_flag();
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void update_actor_status_and_mp();
extern s16 sample_terrain_surface_height();
extern s32 check_action_eligibility_updates_actor_state_directional_animation_success();
extern s16 actor_turn_angle_offsets[8];
extern u8 reference_tile_object[];
extern s8 reference_tile_position_alias;
void update_actor_movement_choosing_direction_recording_path(u8 *move_work, void *entry_context, SpriteFrameState *position, ActorRecord *actor);
#endif

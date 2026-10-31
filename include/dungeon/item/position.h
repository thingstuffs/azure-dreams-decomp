#ifndef DUNGEON_ITEM_POSITION_H
#define DUNGEON_ITEM_POSITION_H
/* Prototypes of the functions defined in src/dungeon/item/position/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity.h"

/* apply_holy_beam_tile_item.c */
s32 apply_holy_beam_tile_item(ActorRecord *body, DungeonItemEntry *object_data, s16 action_type);

/* apply_malicious_light_tile_item.c */
s32 apply_malicious_light_tile_item(void *actor, DungeonItemEntry *item, s16 action);

/* create_and_initialize_player_tile_actor.c */
s32 create_and_initialize_player_tile_actor(void);

/* find_neighbor_with_negative_tile_probe.c */
s32 find_neighbor_with_negative_tile_probe(u8 *entity, s16 *direction);

/* find_neighbor_with_nonnegative_tile_probe.c */
s32 find_neighbor_with_nonnegative_tile_probe(u8 *object, s16 *direction_out);

/* forward_monster_coordinate_delta.c */
s32 calculate_planar_heading(s16 start_x, s16 start_y, s16 end_x, s16 end_y);

/* is_map_coordinate_out_of_bounds.c */
s32 is_map_coordinate_out_of_bounds(s16 x, s16 y);

#endif

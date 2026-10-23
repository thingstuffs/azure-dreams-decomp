#ifndef DUNGEON_LEVEL_H
#define DUNGEON_LEVEL_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void bank_selector_no_op(s32 selector);
s32 find_first_free_map_entry(void);
s32 find_valid_nearby_position(u8 *entry, s16 target_x, s16 target_y, s16 *out_x, s16 *out_y);
s32 is_neighbor_tile_blocked(s16 origin_x, s16 origin_y, s32 direction);

s32 select_floor_item_with_special_overrides(s8 *out_group, s8 *out_index, s32 unused, s32 skip_special);
void setup_run_and_load_track(void);
s32 traverse_nodes_and_render_unflagged(void *start_node);


void render_projected_sprite_with_depth_bias(ObjectPosition *position, void *sprite, s16 world_z, s32 depth_bias);

void install_trap_handler_after_floor_trap_check(void *owner, s32 context, void *source, void *target);

#endif

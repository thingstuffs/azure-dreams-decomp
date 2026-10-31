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

/* dungeon/level/terrain_surface_height_g00351.c */
s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);

/* dungeon/level/tile.c */
void cycle_map_cell_flags(s16 x, s16 y, u16 flags);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 select_and_initialize_entry_at_position(s16 x, s16 y, s16 z, s32 type_id, s32 entry_value);

void process_unflagged_linked_entries(s32 firstEntryBase);
void process_unflagged_linked_entries_alt(s32 firstNodeBase);

void func_800BCFBC(s32 selector);

struct Source;
s32 call_slot_handler_and_update_status(s32 handler_id, void *object_ptr, s32 slot_id, s8 update_state);
void *spawn_object_at_target_position(ActorRecord *source, s16 target_x, s16 target_y);
s32 update_object_coordinates_if_valid(SpriteFrameState *object, EntityRec *context);

s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);

#endif

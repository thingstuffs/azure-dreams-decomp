#ifndef DUNGEON_LEVEL_H
#define DUNGEON_LEVEL_H
#include "common.h"
#include "dungeon/level/tile_flags.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* MapGrid.cells contains six-byte entries. The terrain sampler and the
 * settling-mesh constructor use the same index into MapGrid.cell_faces. */
typedef struct TerrainMapCell {
    u16 face_index;
    s16 height_offset;
    u16 flags;
} TerrainMapCell;

void bank_selector_no_op(s32 selector);
s32 find_first_free_map_entry(void);
s16 find_entry_at_tile_coordinates(s16 x, s16 y, s16 z);
s32 find_valid_nearby_position(u8 *entry, s16 target_x, s16 target_y, s16 *out_x, s16 *out_y);
s32 is_neighbor_tile_blocked(s16 origin_x, s16 origin_y, s32 direction);

s32 select_floor_item_with_special_overrides(s8 *out_group, s8 *out_index, s32 unused, s32 skip_special);
void build_dungeon_floor(void);
struct TrackedSpriteEffect;
s32 traverse_nodes_and_render_unflagged(struct TrackedSpriteEffect *node);


void render_projected_sprite_with_depth_bias(ObjectPosition *position, SpriteFrameState *sprite, s16 world_z, s32 depth_bias);

void install_trap_handler_after_floor_trap_check(void *owner, s32 context, void *source, void *target);

/* dungeon/level/terrain_surface_height_g00351.c */
s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);


/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 place_floor_trap_at_tile(s16 x, s16 y, s16 z, s32 type_id, s32 entry_value);

void process_unflagged_linked_entries(void *firstEntryBase);
void process_unflagged_linked_entries_alt(void *firstNodeBase);

void func_800BCFBC(s32 selector);

struct Source;
s32 call_slot_handler_and_update_status(s32 handler_id, void *object_ptr, s32 slot_id, s8 update_state);
void *get_lift_target_at_tile(ActorRecord *source, s16 target_x, s16 target_y);
s32 update_object_coordinates_if_valid(SpriteFrameState *object, EntityRec *context);

s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);

s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
void clear_slot_and_detach_entity(s32 slot_index);
s32 render_active_sprite_parts_and_shadows(void *unused_0, void *unused_1, SpriteFrameState *render_params);

#include "shared/object_node.h"
void insert_node_before_primary_actor(ObjectNodeHeader *entry);

#endif

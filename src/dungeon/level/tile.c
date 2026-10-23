
struct ObjectNodeHeader;
/* Complete native TU in retail file order. Review pending. */
#include "dungeon/level/tile.h"
#include "shared/object_node.h"
#include "dungeon/level/outer_ring.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"
#include "dungeon/level.h"

typedef struct {
    s8 pad_00[0x14];
    u32 flags_14;
    u8 pad_18[4];
    u32 flags_1C;
    u8 pad_20[0x21];
    s8 field_41;
    s8 field_42;
    u8 pad_43[0x29];
    u16 value_6C;
    s16 velocity_6E;
    u8 pad_70;
    u8 field_71;
} Entity94744;

/* Apply scaled velocity and reset the entity motion state. */
void apply_scaled_entity_velocity(Entity94744 *entity) {
    entity->field_71 = 0x80;
    entity->value_6C += ((s32)(entity->velocity_6E * g_dungeon_status.turn_scale)) >> 8;
    entity->field_42 = 0;
    entity->field_41 = 0;
    entity->flags_1C &= 0x7FFFFFFF;
    entity->flags_14 &= 0x7FFE7FFF;
}
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"

void apply_scaled_entity_velocity();                      /* extern */

typedef struct S_80099F04_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_80099F04_1;

/* Walk the linked entries and process those without flag 0x4000. */
void process_unflagged_linked_entries(s32 firstEntryBase) {
    S_80099F04_1 *entry;

    entry = firstEntryBase + 0x20;
    if (entry != ((EntityRec *)(((s32 *)&primary_actor_record)))->x.v) {
        do {
            if (!(entry->unk_14 & 0x4000)) {
                apply_scaled_entity_velocity(entry);
            }
            entry = entry->unk_5C + 0x20;
        } while (entry != ((EntityRec *)(((s32 *)&primary_actor_record)))->x.v);
    }
}
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
void apply_scaled_entity_velocity();                      /* extern */

typedef struct S_80099F70_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_80099F70_1;

// Process linked entries with flag 0x4000 until reaching the global sentinel.
void process_unflagged_linked_entries_alt(s32 firstNodeBase) {
    S_80099F70_1 *currentEntry;

    currentEntry = firstNodeBase + 0x20;
    if (currentEntry != ((EntityRec *)(((s32 *)&primary_actor_record)))->x.v) {
        do {
            if (currentEntry->unk_14 & 0x4000) {
                apply_scaled_entity_velocity(currentEntry);
            }
            currentEntry = currentEntry->unk_5C + 0x20;
        } while (currentEntry != ((EntityRec *)(((s32 *)&primary_actor_record)))->x.v);
    }
}
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"

typedef struct S_80099FDC_2 {
    u8 pad_00[0x58];
    void * unk_58;
    void * unk_5C;
} S_80099FDC_2;

typedef struct S_80099FDC_3 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_80099FDC_3;

/* Clear the entry flag and link the entry into the current owner list. */
void clear_entry_flag_and_link_owner(ObjectNodeHeader *entry)
{
    S_80099FDC_2 *entry_links;
    S_80099FDC_3 *neighbor_links;
    ActorRecord *owner;

    owner = primary_actor_record;
    entry->unk_10 = *(s32 *)&entry->unk_10 & 0x7FFFFFFF;
    neighbor_links = (u8 *)owner->previous_actor_header + 0x20;
    entry_links = (u8 *)entry + 0x20;
    entry_links->unk_5C = neighbor_links->unk_5C;
    entry_links->unk_58 = owner->previous_actor_header;
    owner->previous_actor_header = entry;
    neighbor_links->unk_5C = entry;
}
#include "modules/dungeon_engine_tile_map_fragment_b48c8.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern EntityLinkNode *actor_update_node_cursor;

/* Unlink a node and advance the global cursor if it references that node. */
void unlink_entity_node(EntityLinkNode *node) {
    EntityLinkNode *prev;
    EntityLinkNode *next;

    if (actor_update_node_cursor == (EntityLinkNode *)((s8 *)node - 0x20)) {
        actor_update_node_cursor = node->next;
    }

    prev = node->prev;
    next = node->next;
    if ((prev != NULL) && (next != NULL)) {
        prev->unk7C = next;
        next->unk78 = prev;
        node->next = NULL;
        node->prev = NULL;
    }
}
#include "modules/dungeon_engine_tile_map_fragment_b48c8.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"

/* Mark and process entries without flag 0x4000, then set the global update flag. */
void process_unflagged_entries_and_set_update(void)
{
    void *entry;
    ObjectNodeHeader *node;
    void *next_entry;

    entry = dungeon_actor_ring_anchor;
    do {
        node = *(void **)((u8 *)entry + 0x5C);
        next_entry = (u8 *)node + 0x20;
        if (!(*(s32 *)((u8 *)entry + 0x14) & 0x4000)) {
            node = (u8 *)entry - 0x20;
            node->flags = (u16)(node->flags | 0x1000);
            unlink_entity_node(entry);
        }
        entry = next_entry;
    } while (entry != dungeon_actor_ring_anchor);

    dungeon_floor_flags = dungeon_floor_flags | 0x10000000;
}
#include "modules/dungeon_engine_tile_map_fragment_b48c8.h"
#include "common.h"

/* Linked-list node with a next pointer at offset 0x0 and a 16-bit
 * flags/state field at offset 0x1E (shared shape with integrate_active_node_vectors's
 * D_80081498 view). */

/* D_80081498 is accessed via %hi/%lo, so its containing symbol must be
 * larger than the -G8 small-data threshold; pad it out. */
extern struct {
    ActiveNode *head;
    int pad[2];
} active_node_list_head;

extern s32 D_80012090[];

extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *entry);

/* Process nodes flagged 0x1000 and clear global bit 28 when D_80012090 is not 1. */
void process_flagged_nodes_and_clear_global_bit(void) {
    ActiveNode *node = active_node_list_head.head;

    if (node != 0) {
        do {
            if (node->field_1E & 0x1000) {
                clear_entry_flag_and_link_owner(node);
            }
            node = node->next;
        } while (node != 0);
    }
    if (*(s32 *)0x80012090 != 1) {
        dungeon_floor_flags &= 0xEFFFFFFF;
    }
}
#include "modules/dungeon_engine_tile_map_fragment_b48c8.h"
#include "common.h"
#include "shared/entity.h"

typedef struct S_8009A180_2 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8009A180_2;

/* Marks an actor processed and moves it beside the anchor in the actor ring unless already marked. */
s32 check_entity_relation(ActorRecord *entry, ActorRecord *anchor) {
    u32 link_bits;
    u32 link_bits_2;
    s32 state_flags;
    s32 anchor_flags;
    s32 prev_link;
    S_8009A180_2 *prev_node;

    if (entry == anchor) {
        anchor_flags = anchor->flags1C;
        anchor->flags1C = anchor_flags | ((u32)(0x80000000));
        return 0;
    }

    state_flags = entry->flags1C;
    if (state_flags < 0) {
        return 0;
    }

    prev_link = 0x80000000;
    state_flags |= prev_link;
    entry->flags1C = state_flags;
    link_bits_2 = (u32)entry;
    unlink_entity_node((void *)link_bits_2);

    prev_link = anchor->next_actor_header;
    entry->next_actor_header = prev_link;
    prev_node = (void *)(prev_link + 0x20);
    link_bits = (u32)prev_node->unk_58;
    entry->previous_actor_header = (void *)link_bits;
    link_bits = (u32)((u8 *)entry - 0x20);
    prev_node->unk_58 = (void *)link_bits;
    anchor->next_actor_header = (void *)link_bits;
    return 1;
}
#include "modules/dungeon_engine_tile_map_fragment_b48c8.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s16 unk0;
    u16 unk2;
    u16 flags;
} MapCell;

typedef struct {
    u8 pad0[0x1DC];
    MapCell *map;
    u8 pad1E0[0x10];
    s16 mapShift;
} DungeonState;

/* Sets map cell flags or cycles the selected flag fields. */
void cycle_map_cell_flags(s16 x, s16 y, u16 flags)
{
    GameWork *state = &g_game_work;
    MapCell *cell;
    u16 cycled_flags;
    u16 new_flags;

    cell = &(*(MapCell **)&state->map.cells)[x + (y << state->map.shiftX)];
    if (flags & 0xC832) {
        new_flags = cell->flags | flags;
    } else {
        cycled_flags = ((cell->flags & flags) + (flags & 0x1100)) & 0x3300;
        cell->flags &= ~flags;
        if (cycled_flags == 0) {
            if (flags == 0x300) {
                cycled_flags = 0x300;
            } else {
                cycled_flags = 0x3000;
            }
        }

        new_flags = cell->flags | cycled_flags;
    }
    cell->flags = new_flags;
}
#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

/* Checks whether the adjacent tile has masked flags or a zero tile value. */
s32 is_neighbor_tile_blocked(s16 origin_x, s16 origin_y, s32 direction) {
    s32 tile_index;
    s32 tile_y;
    s32 result;
    GameWork *dungeon;
    u8 *tile;

    dungeon = &g_game_work;
    do {
    } while (0);
    tile_index = origin_x + ((s16 *)((u8 *)dir_step_x))[(s16)direction];
    tile_y = origin_y + ((s16 *)((u8 *)dir_step_y))[(s16)direction];
    tile_index += tile_y << dungeon->map.shiftX;
    tile = ((u8 *)dungeon->map.cells) + tile_index * 6;
    result = *(u16 *)(tile + 4) & 0xF320;
    if (result != 0) {
        result = 1;
        return result;
    }
    result = *(u16 *)tile;
    if (result != 0) {
        result = 0;
        return result;
    }
    result = 1;
    return result;
}

/* MECHANISM: Frameless leaf; ASM_KEEP holds D_80083160 at words 0-1.
   Symbolic s16 indexing reproduces the interleaved argument normalization.
   One v0 result lifetime plus an epilogue barrier prevents tail duplication. */
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef struct {
    s16 value;
    s16 unk2;
    u16 flags;
} Entry;

/* Returns the grid entry value at the selected offset and writes its flags. */
s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags)
{
    s32 grid_x;
    s32 grid_y;
    s32 entry_index;
    GameWork *state;
    Entry *entry;

    grid_x = x + dir_step_x[offset_index];
    state = &g_game_work;
    grid_y = y + dir_step_y[offset_index];
    entry_index = grid_x + (grid_y << state->map.shiftX);
    entry = (Entry *)((entry_index * sizeof(Entry)) +
                      (unsigned long)((Entry *)state->map.cells));
    *flags = entry->flags;
    return entry->value;
}
#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad[4];
    u16 flags;
} DungeonCell;

s32 count_floor_items_at_tile(s16 first_key, s16 second_key);

/* Clears selected cell flags or decrements their encoded value, clamping at zero. */
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags)
{
    DungeonCell *cells;
    MapGrid *map;

    cells = (DungeonCell *)g_game_work.map.cells;
    map = &g_game_work.map;
    if (flags & 0x8832) {
        if (flags & 0x800) {
            s16 cell_x = x;
            s16 cell_y = y;

            if ((s16)count_floor_items_at_tile(cell_x, cell_y) >= 2) {
                return;
            }
            cells[cell_x + (cell_y << map->shiftX)].flags &= ~flags;
        } else {
            cells[(s16)x + ((s16)y << map->shiftX)].flags &= ~flags;
        }
    } else {
        s32 cell_x = (s16)x;
        s32 cell_y = (s16)y;
        s32 i;
        u16 old_flags;
        s16 remainder;

        i = cell_x + (cell_y << map->shiftX);
        old_flags = cells[i].flags;
        remainder = (old_flags & flags) - (flags & 0x1100);
        cells[i].flags = old_flags & ~flags;
        if (remainder < 0) {
            remainder = 0;
        }
        cells[cell_x + (cell_y << map->shiftX)].flags |= remainder;
    }
}
#include "modules/dungeon_engine_tile_map_abi_views.h"
extern s16 direction_y_offsets[];
extern s16 direction_x_offsets[];
#include "common.h"

extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);

/* Checks the sides of a diagonal direction for terrain above 0x200. */
s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height)
{
    s32 tile_flags;
    s32 side;
    u32 dir;
    s16 saved;
    s16 h;
    s32 x;
    s32 y;

    saved = direction;
    h = height;
    if (direction & 1) {
        x = tile_x;
        y = tile_y;
        for (side = -1; side < 2; side += 2) {
            if (get_offset_map_cell_value_and_flags(x, y, (saved + side) & 7, &tile_flags) != 0) {
                dir = ((u16)saved + side) & 7;
                if (map_height_wrapped((x << 6) + 0x20 + ((u16 *)direction_x_offsets)[dir], (y << 6) + 0x20 + ((u16 *)direction_y_offsets)[dir], h) > 0x200) {
                    break;
                }
            }
        }
        if (side < 2) {
            return 0;
        }
    }
    return 1;
}
#include "modules/dungeon_engine_tile_map_fragment_b4f0c.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/dir_step.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s16 find_active_rect_containing_point(u16, u16);

extern s16 direction_x_offsets[];
extern s16 direction_y_offsets[];

/* Checks movement clearance and classifies the destination height relative to the actor. */
s32 check_movement_clearance_and_height(u32 move_flags, FuncArg1 *position, FuncArg2 *actor, s16 height_offset) {
    s16 offset_or_height;
    s32 call_direction;
    s16 *x_table;
    u16 flags;
    u16 *flags_out;
    s32 direction;
    u32 x_shifted;
    u32 y_shifted;
    s32 x_base;
    s32 y_base;
    u16 x_pos;
    s32 y_pos;
    u16 height;
    s16 monster_index;
    s32 dest_height;
    s32 signed_height;
    s32 status;

    direction = (move_flags >> 9) & 7;
    height = actor->height;
    x_shifted = position->x << 6;
    y_shifted = position->y << 6;
    x_base = x_shifted + 0x20;
    y_base = y_shifted + 0x20;

    if ((check_diagonal_side_height(direction, (u32)x_base >> 6, (u32)y_base >> 6,
                       (s16)(height - height_offset)) << 16) != 0) {

        call_direction = direction;
        flags_out = &flags;
        x_table = direction_x_offsets;
        offset_or_height = call_direction << 1;
        x_pos = *(u16 *)((u8 *)x_table + offset_or_height) + x_base;
        y_pos = *(u16 *)((u8 *)direction_y_offsets + offset_or_height) + y_base;
        if ((get_offset_map_cell_value_and_flags(position->x, position->y, call_direction, flags_out) << 16) == 0) {
            return 0;
        }

        if (position->flag < 0) {
            monster_index = find_active_rect_containing_point(
                (u16)(position->x +
                      *(u16 *)((u8 *)dir_step_x + offset_or_height)),
                (u16)(position->y +
                      *(u16 *)((u8 *)dir_step_y + offset_or_height)));
            if (monster_index >= 0 &&
                (dungeon_rooms[monster_index].flags & 2) &&
                !(actor->flags & 0x2000)) {
                return 0;
            }
        }

        if (flags & 0x8402) {
            return 0;
        }

        if (flags & 0x3300) {
            s32 y_coord;
            s32 x_coord;

            if (!(flags & 0x40)) {
                status = -1;
                return status;
            }
            x_pos &= 0xFFFF;
            x_coord = x_pos;
            y_coord = y_pos & 0xFFFF;
            offset_or_height = terrain_height_short(x_coord, y_coord, (s16)(height - height_offset));
            if (find_eligible_actor_at_tile_and_height(actor, (u32)x_pos >> 6, (u32)y_coord >> 6,
                              (s16)offset_or_height)) {
                status = -1;
                return status;
            }
        } else {
            offset_or_height = terrain_height_short(x_pos & 0xFFFF, y_pos & 0xFFFF,
                                   (s16)(height - height_offset));
        }

        status = (u32)offset_or_height << 16;
        dest_height = status >> 16;
        if (dest_height >= 0x200) {
            return 0;
        }
        status = (u32)height << 16;
        signed_height = status >> 16;
        if (dest_height == signed_height) {
            return 1;
        }
        if (signed_height < dest_height) {
            return 2;
        }
        return 3;
    }
    return 0;
}
#include "modules/dungeon_engine_tile_map_fragment_b4f0c.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef struct {
    u16 value;
    u8 pad02[6];
} StackU16;

extern s16 direction_x_offsets[];
extern s16 direction_y_offsets[];
s16 find_active_rect_containing_point(u16, u16);

/* Check a directional move against map bounds, collisions, monsters, and floor height. */
s32 check_directional_move_and_terrain(u32 move_flags, FuncArg1 *actor, FuncArg2 *body, u16 height_offset) {
    StackU16 collision;
    s16 monster_index;
    /* The actor is finished before the floor-height samples begin. */
    FuncArg1 * actor_or_height;
    s32 target_height;
    u32 direction_bits;
    u8 *x_steps;
    s32 direction;
    s32 coord_work;
    s32 coord_work_2;
    u32 target_x;
    s32 step_offset;
    u32 offset_work;
    s32 result;
    s32 coord_or_height;
    s32 next_x;
    MapGrid *map_limits;
    u16 *x_step;
    u16 *y_step;
    u16 height;
    u32 target_y_u16;
    u32 center_y;
    u8 direction_arg;
    s16 direction_or_x;
    s32 tile_coord;
    s32 y_or_direction;
    u32 collision_out;
    u16 tile_x8;
    u16 tile_y8;

    actor_or_height = actor;
    direction_bits = (move_flags >> 9) & 7;
    direction_arg = direction_bits;
    direction = (s16)direction_bits;
    x_steps = (u8 *)dir_step_x;
    step_offset = direction * 2;
    x_step = (u16 *)((s32)step_offset + (s32)x_steps);
    coord_or_height = actor_or_height->x;
    offset_work = *x_step;
    direction_or_x = direction_arg;
    target_x = coord_or_height + offset_work;
    map_limits = &g_game_work.map;
    next_x = target_x & 0xFFFF;
    if (next_x != 0) {
        if (((1 << map_limits->shiftX) - 1) >= next_x) {
            y_step = (u16 *)((u8 *)dir_step_y + step_offset);
            coord_or_height = actor_or_height->y;
            offset_work = *y_step;
            coord_work = coord_or_height + offset_work;
            coord_or_height = coord_work & 0xFFFF;
            if (coord_or_height != 0) {
                if (((1 << map_limits->shiftY) - 1) >= coord_or_height) {
                    tile_x8 = actor_or_height->x;
                    tile_y8 = actor_or_height->y;
                    coord_or_height = tile_x8;
                    offset_work = tile_y8;
                    height = body->height;
                    coord_or_height <<= 6;
                    coord_work_2 = coord_or_height + 0x20;
                    tile_coord = (s16)coord_work_2 >> 6;
                    offset_work <<= 6;
                    center_y = offset_work + 0x20;
                    y_or_direction = (s16)center_y >> 6;
                    coord_or_height = (s16)(height - height_offset);
                    result = clearance_word_coords(direction_or_x, tile_coord, y_or_direction,
                                           coord_or_height) << 0x10;
                    if (result != 0) {
                        y_or_direction = direction;
                        collision_out = (u32)&collision.value;
                        {
                            u16 *pa = (u16 *)((u8 *)direction_x_offsets + step_offset);
                            u16 *pb = (u16 *)((u8 *)direction_y_offsets + step_offset);
                            target_x = *pa + coord_work_2;
                            coord_work = *pb + center_y;
                        }
                        get_offset_map_cell_value_and_flags(actor_or_height->x, actor_or_height->y,
                                     y_or_direction, (u16 *)collision_out);
                        if ((collision.value & 0x8002) != 0) {
                            result = 0;
                            return 0;
                        }
                    } else {
                        result = 0;
                        return 0;
                    }
                    if (!((actor_or_height->flag >= 0) ||
                        (monster_index = find_active_rect_containing_point((actor_or_height->x + *x_step) & 0xFFFF,
                                                       (actor_or_height->y + *y_step) & 0xFFFF),
                         (monster_index < 0)) ||
                        !(dungeon_rooms[monster_index].flags & 2) ||
                        (result = 0, ((body->flags & 0x2000) != 0)))) {
                        return result;
                    }
                    if (collision.value & 0x3300) {
                        target_x &= 0xFFFF;
                        if (collision.value & 0x40) {
                            {
                                u16 sample_x;
                                sample_x = target_x;
                                target_y_u16 = coord_work & 0xFFFF;
                                actor_or_height = (FuncArg1 *)(sample_terrain_surface_height(
                                    sample_x, target_y_u16, (s16)(height - height_offset)));
                            }
                            tile_coord = target_x >> 6;
                            y_or_direction = target_y_u16 >> 6;
                            target_height = (s16)((s32)actor_or_height);
                            if (target_height >= 0x201) {
                                target_height = (s16)body->height;
                            }
                            /* Target X is dead after the tile argument is formed. */
                            target_x = find_eligible_actor_at_tile_and_height(body, tile_coord, y_or_direction, target_height);
                            if (target_x != 0) {
                                return -1;
                            }
                        } else {
                            return -1;
                        }
                    } else {
                        actor_or_height = (FuncArg1 *)(sample_terrain_surface_height(
                            target_x & 0xFFFF, coord_work & 0xFFFF, (s16)(height - height_offset)));
                    }
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
    result = -1;
    coord_or_height = ((s32)actor_or_height) << 0x10;
    coord_or_height >>= 0x10;
    coord_or_height = coord_or_height < 0x201;
    if (coord_or_height) {
        result = 1;
    }
    return result;
}
#include "modules/dungeon_engine_tile_map_fragment_b4f0c.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
} Func95440Input;


typedef struct {
    u8 pad0[0x14];
    u32 mask14;
    u8 pad18[4];
    u32 flags1c;
    u8 pad20[0x4c];
    s16 value6c;
    s16 value6e;
} Func95440Object;

/* Checks the adjacent tile and classifies its height relative to the source height. */
s32 classify_adjacent_tile_height(u32 direction_bits, Func95440Input *position, SpriteFrameState *actor, u32 source_height,
    s32 height_offset) {
    u16 tile_flags;
    s32 target_height;
    s16 initial_height;
    s32 saved_height;
    u32 direction;
    s32 y;
    s32 x;
    u16 wrapped_x;
    u16 wrapped_y;
    s32 signed_height;
    s32 level_result;
    Func95440Object *object;

    direction = (direction_bits >> 9) & 7;
    x = position->x;
    y = position->y;
    initial_height = (s16)(source_height - height_offset);
    saved_height = source_height;
    if ((check_diagonal_side_height(direction, x >> 6, y >> 6, initial_height) << 16) == 0) {
        return -2;
    }
    target_height = initial_height;

    x += dir_step_x[direction] << 6;
    y += dir_step_y[direction] << 6;
    if ((get_offset_map_cell_value_and_flags(actor->unk_24, actor->unk_25, direction, &tile_flags) << 16) == 0) {
        return 0;
    }
    if (tile_flags & 0x8000) {
        return -2;
    }
    if (tile_flags & 0x400) {
        return 0;
    }

    if (tile_flags & 0x3300) {
        wrapped_x = x;
        wrapped_y = y;
        target_height = terrain_height_words(wrapped_x, wrapped_y, target_height);
        x = wrapped_x;
        y = wrapped_y;
        object = find_eligible_actor_at_tile_and_height(((s32)primary_actor_record), x >> 6, y >> 6, (s16)target_height);
        if (object != 0) {
            if (object->flags1c & 0x2000) {
                if (!(object->flags1c & 0x628)) {
                    if (!(object->mask14 & 0x40000000)) {
                        if (object->value6c + ((object->value6e * g_dungeon_status.turn_scale) >> 8) < 0x100) {
                            return -1;
                        }
                    } else {
                        return -1;
                    }
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        }
    } else {
        target_height = terrain_height_words(x & 0xffff, y & 0xffff, target_height);
    }

    signed_height = (target_height << 16) >> 16;
    if (signed_height < 0x200) {
        level_result = 1;
        if (signed_height == (s16)saved_height) {
            return level_result;
        }
        if ((s16)saved_height < signed_height) {
            if ((signed_height - (s16)saved_height) >= 0x41) {
                return 4;
            }
            return 2;
        }
        return 3;
    }
    return -2;
}
#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef unsigned long uptr;

typedef struct S_8009ADB8_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8009ADB8_0;   /* arg0 in can_push_adjacent_actor */

typedef struct S_8009ADB8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009ADB8_1;   /* arg1 in can_push_adjacent_actor */

typedef struct S_8009ADB8_2 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_8009ADB8_2;   /* map_state in can_push_adjacent_actor */

typedef struct {
    u16 type;
    u16 unk2;
    u16 flags;
} FacingMapCell;

extern s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);

/* Checks the facing cell for valid terrain flags and an acceptable height. */
s32 can_push_adjacent_actor(S_8009ADB8_0 *facing_state, S_8009ADB8_1 *attributes, s16 tile_x, s16 tile_y,
    s16 initial_height)
{
    FacingMapCell *map;
    u8 *map_state;
    s16 height;
    s32 next_height;
    s32 direction;
    s16 next_x;
    s16 next_y_sum;
    s16 next_y;
    FacingMapCell *next_cell;

    map = ((FacingMapCell *)g_game_work.map.cells);
    map_state = (u8 *)((FacingMapCell **)&g_game_work.map.cells);
    direction = (facing_state->unk_2A >> 9) & 7;
    if (!(attributes->unk_14 & 0x100) ||
        (height = sample_terrain_surface_height(
             (((tile_x << 16) >> 10) + 0x20) & 0xFFE0,
             (((tile_y << 16) >> 10) + 0x20) & 0xFFE0,
             initial_height),
         height >= 0x200)) {
        return 0;
    }

    next_x = tile_x + ((u16 *)dir_step_x)[direction];
    next_y_sum = tile_y + ((u16 *)dir_step_y)[direction];
    next_y = (s16)next_y_sum;
    next_cell = (FacingMapCell *)((uptr)((s16)(next_x +
        (next_y << ((S_8009ADB8_2 *)map_state)->unk_14)) * 6) + (uptr)map);

    if (!(next_cell->flags & 0xB300)) {
        if (next_cell->type != 0) {
            next_height = sample_terrain_surface_height(
                (((next_x << 16) >> 10) + 0x20) & 0xFFE0,
                ((next_y << 6) + 0x20) & 0xFFE0,
                height) << 16;
            next_height >>= 16;
            if (next_height < 0x200) {
                return 1;
            }
        }
    }
    return 0;
    return 1;
}
#include "modules/dungeon_engine_tile_map_abi_views.h"
extern s16 direction_y_offsets[];
extern s16 direction_x_offsets[];
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 pad0A[0xA];
    s16 height;
} PositionHeightView;

extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
struct Node;
s32 is_map_coordinate_out_of_bounds();                        /* extern */
extern s8 D_800DD7DC;

typedef struct S_8009AF18_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009AF18_0;   /* arg2 in measure_directional_stopping_distance */

typedef struct S_8009AF18_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8009AF18_2;

typedef struct S_8009AF18_3 {
    u8 pad_00[0x124];
    void * unk_124;
} S_8009AF18_3;   /* *(void **)(page + 0x3D7C) in measure_directional_stopping_distance */

typedef struct S_8009AF18_4 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8009AF18_4;   /* ((S_8009AF18_3 *)(*(void **)(page + 0x3D7C)))->unk_124 in measure_directional_stopping_distance */

/* Checks successive tiles in a direction and returns the stopping distance. */
s32 measure_directional_stopping_distance(u32 direction_flags, PositionHeightView *origin, S_8009AF18_0 *start_tile, u16 max_steps) {
    u16 tile_flags;
    s32 direction_index;
    s32 direction;
    s32 height_result;
    s32 check_x;
    s16 step;
    s32 world_y;
    s32 world_x;
    s32 tile_x;
    s32 tile_y;
    S_8009AF18_2 *occupant;

    step = 1;
    D_800DD7DC = 0;
    tile_x = start_tile->unk_24;
    tile_y = start_tile->unk_25;
    direction_index = (direction_flags >> 9) & 7;
    world_x = (tile_x << 6) | 0x20;
    world_y = (tile_y << 6) | 0x20;
    if ((s16)max_steps > 0) {
        direction = direction_index;
        do {
            check_x = (s16) tile_x;
            if (is_map_coordinate_out_of_bounds(check_x, (s16) tile_y) != 0) {
                return (s16) (step - 1);
            }
            if ((get_offset_map_cell_value_and_flags(check_x, (s16) tile_y, direction, &tile_flags) << 0x10) != 0) {
                tile_x += (u16)dir_step_x[direction];
                tile_y += (u16)dir_step_y[direction];
                if (tile_flags & 0x3300) {
                    {
                        ActorRecord *world;

                        world = dungeon_actor_ring_anchor;
                        occupant = tile_finder_words(world, tile_x & 0xFFFF, tile_y & 0xFFFF, world->ground_height);
                    }
                    if (occupant != NULL) {
                        if (occupant->unk_13 == 0x1F) {
                            if (!(occupant->unk_1C & 0x228)) {
                                if (((S_8009AF18_4 *)(((S_8009AF18_3 *)(void *)dungeon_actor_ring_anchor)->unk_124))->unk_13 < 0) {
                                    D_800DD7DC = 1;
                                    occupant->unk_14 |= 0x800000;
                                }
                            }
                        }
                    }
                    return (s16)step;
                }
                world_x += ((u16 *)direction_x_offsets)[direction];
                world_y += ((u16 *)direction_y_offsets)[direction];
                height_result = map_height_short(world_x & 0xFFFF, world_y & 0xFFFF, origin->height);
                if (height_result >= 0x200) {
                    return (s16) (step - 1);
                }
            } else {
                return (s16) (step - 1);
            }
            step++;
        } while (step <= (s16)max_steps);
    }
    return (s16)step;
}

#include "modules/dungeon_engine_tile_map_abi_views.h"
#include "common.h"
#include "shared/dir_step.h"

typedef struct {
    s32 unk0[2];
    s32 unk8;
    s32 unkC[2];
    s32 unk14;
} Arg1;

typedef struct {
    u8 pad0[0x24];
    u8 x;
    u8 y;
} Arg2;

extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);

/* Checks the neighboring tile in the encoded direction for blocking flags and height. */
s32 check_neighbor_tile_blocking(u32 direction_bits, Arg1 *state_in, Arg2 *position_in) {
    u16 tile_flags;
    Arg1 *state;
    Arg2 *position;
    s32 direction;
    s32 next_x;
    s32 next_y;

    state = state_in;
    position = position_in;
    direction = (direction_bits >> 9) & 7;
    if ((get_offset_map_cell_value_and_flags(position->x, position->y, direction, &tile_flags) << 0x10) != 0) {
        if (tile_flags & 0x8000) {
            return 0;
        }
        next_x = position->x + ((u16 *)dir_step_x)[direction];
        next_y = position->y + ((u16 *)dir_step_y)[direction];
        if (map_height_short((((s32) (next_x << 0x10) >> 0xA) | 0x20) & 0xFFE0,
            (((s32) (next_y << 0x10) >> 0xA) | 0x20) & 0xFFE0, (s32) (state->unk8 + (state->unk14 * 2)) >> 0x10)
            < 0x200) {
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}
#include "common.h"

typedef struct Node Node;
typedef struct {
    u8 pad0[0x24];
    u8 x;
    u8 y;
} Owner;

struct Node {
    u8 pad0[0x5C];
    Node *next;
    u8 pad60[0x28];
    s16 value;
};

extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);

/* Finds an eligible node at the target coordinates with a value difference below 64. */
void *find_eligible_actor_at_tile_and_height(Node *node, s16 x, s16 y_in, s16 value) {
    s16 y;
    u16 flags;
    Node *sentinel;
    Owner *owner;
    s32 value_gap;
    u16 target_x;
    s16 target_value;

    target_x = x;
    target_value = value;
    y = y_in;
    if ((s16)get_offset_map_cell_value_and_flags((s16)(x - 1), y, 0, &flags) == 0) {
        return 0;
    }
    if (!(flags & 0x3300)) {
        return 0;
    }
    sentinel = node;
    node = (Node *)((u8 *)node->next + 0x20);
    while (node != sentinel) {
        owner = *(Owner **)((u8 *)node - 0x14);
        if (owner->x == target_x && owner->y == (u16)y) {
            value_gap = node->value - target_value;
            if (value_gap < 0) {
                value_gap = -value_gap;
            }
            if (value_gap < 0x40 && (check_entity_eligibility(node) << 16) != 0) {
                return node;
            }
        }
        node = (Node *)((u8 *)node->next + 0x20);
    }
    return 0;
}

#include "common.h"
#include "shared/record_ptrs.h"

extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);

/* Find an eligible object at the tile within 64 units of the target height. */
void *find_object_near_tile_height(s16 tile_x, s16 tile_y, s16 target_height)
{
    u16 flags;
    s32 height_delta;
    void *first_object;
    void *object;
    void *tile;

    if ((get_offset_map_cell_value_and_flags((u16)(tile_x - 1), tile_y, 0, &flags) << 16) == 0) {
        return 0;
    }
    if (!(flags & 0x3300)) {
        return 0;
    }

    object = dungeon_actor_ring_anchor;
    first_object = object;
    do {
        tile = ((ObjectNodeHeader *)((u8 *)object - 0x20))->sprite;
        if (*(u8 *)((u8 *)tile + 0x24) == (u16)tile_x &&
            *(u8 *)((u8 *)tile + 0x25) == (u16)tile_y) {
            height_delta = *(s16 *)((u8 *)object + 0x88) - target_height;
            if (height_delta < 0) {
                height_delta = -height_delta;
            }
            if (height_delta < 0x40 &&
                (check_entity_eligibility(object) << 16) != 0) {
                return object;
            }
        }
        object = (u8 *)*(void **)((u8 *)object + 0x5C) + 0x20;
    } while (object != first_object);
    return 0;
}
#include "modules/dungeon_engine_tile_map_fragment_b5d50.h"
#include "shared/game_work.h"

typedef struct Rec
{
    u8 pad[0x5c];
    u8 *next;
}
Rec;
extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
/* Finds an eligible entry at the requested coordinates after checking the tile to the left. */
void *find_eligible_entry_at_coordinates(u8 *entry, s16 x, s16 y)
{
    u16 tile_flags;
    u8 *list_head;
    u16 tile_x;
    u16 tile_y;
    tile_x = x;
    tile_y = y;
    list_head = entry;
    if (((get_offset_map_cell_value_and_flags((s16) (tile_x - 1), y, 0, &tile_flags) << 0x10) == 0) || ((tile_flags & 0x3300) != 0)) {
        entry = ((Rec *) entry)->next + 0x20;
        if (entry != list_head) {
            do {
                u8 *entry_data = *((u8 **) (entry - 0x14));
                if ((((*((u8 *) (entry_data + 0x24))) == tile_x) && ((*((u8 *) (entry_data + 0x25))) == tile_y))
                    && ((check_entity_eligibility(entry) << 0x10) != 0)) {
                    return entry;
                }
                entry = ((Rec *) entry)->next + 0x20;
            }
            while (entry != list_head);
        }
    }
    return 0;
}
#include "modules/dungeon_engine_tile_map_abi_views.h"
#include "modules/dungeon_engine_tile_map_fragment_b5d50.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"

typedef struct Source Source;
typedef struct Spawned Spawned;

extern u8 held_item_record[];

extern s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s32 find_type_13_slot_index(Spawned *);
extern s32 find_floor_item_at_world_position(s32, s32, s32);
extern Spawned *create_indexed_floor_object(void *, s32, s32, void *, void *, s32);
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);

struct Spawned {
    u8 unk00[0x13];
    u8 kind;
    s32 flags;
    u8 unk18[0x1c];
    s32 value34;
    u8 unk38[4];
    s32 value3c;
    u8 unk40[0x40];
    void *parent;
    u8 unk84[0x38];
    void *fieldbc;
};

struct Source {
    u8 unk00[0x2a];
    u16 index_field;
    u8 unk2c[0x5c];
    s16 height;
};

typedef struct Context {
    u8 unk00[8];
    s32 x;
    s32 y;
} Context;

/* Spawns an object at the target position and updates the active source state. */
void *spawn_object_at_target_position(Source *source, s16 target_x, s16 target_y) {
    Source **active_source;
    Spawned *spawned;
    u8 *entry;
    s16 x;
    s32 y;
    s32 state_code;
    s32 probe_result;
    s32 direction;
    s32 flags34;
    s32 flags3c;
    s32 entry_value;
    u8 *result_bytes;
    u16 spawn_x;
    u16 spawn_y;

    direction = (source->index_field >> 9) & 7;

    probe_result = check_diagonal_side_height(direction,
                                 (s16)(target_x - dir_step_x[direction]),
                                 (s16)(target_y - dir_step_y[direction]),
                                 (s16)(source->height - 0x20));
    spawn_x = (u16)target_x;
    spawn_y = (u16)target_y;
    probe_result <<= 0x10;
    active_source = &primary_actor_record;
    if (probe_result == 0) {
        return (void *)0;
    }

    spawned = tile_finder_words(source, spawn_x, spawn_y,
                            source->height);
    if (spawned != (void *)0) {
        if ((spawned->flags & 0x80000) && source == *active_source) {
            held_item_record[0] = spawned->kind;
            held_item_record[1] = 0x13;
            state_code = 0x14;
            if (spawned->flags & 0x4000) {
                state_code = find_type_13_slot_index(spawned);
                if ((s16)state_code < 0) {
                    state_code = 0x14;
                }
            }
            held_item_record[3] = (u8)state_code;
            held_item_record[2] = 0;
        }
        return spawned;
    }

    x = (s16)target_x;
    y = (s16)target_y;
    flags3c = (s16)find_floor_item_at_world_position(x, y, source->height);
    if (flags3c >= 0) {
        entry = &((u8 *)dungeon_ground_items)[flags3c * 4];
        spawned = create_indexed_floor_object(source,
                                ((Context *)((u8 *)source - 0x20))->x,
                                ((Context *)((u8 *)source - 0x20))->y,
                                source, entry, flags3c);
        if (spawned == (void *)0) {
            return (void *)1;
        }
        spawned->parent = source;
        if (source == *active_source) {
            entry_value = *(s32 *)entry;
            spawned->fieldbc = held_item_record;
            *(s32 *)held_item_record = entry_value;
        }
        entry[1] = 0;
        entry[0] = 0;
        update_map_cell_flags_with_item_limit(x, y, 0x800);
        result_bytes = (u8 *)spawned + 0x20;
        flags34 = spawned->value34;
        flags3c = spawned->value3c;
        flags34 |= 0x80000;
        flags3c |= 0x2000;
        spawned->value34 = flags34;
        spawned->value3c = flags3c;
        return result_bytes;
    }
    return (void *)0;
}
#include "modules/dungeon_engine_tile_map_fragment_b5d50.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef union { s16 coordinate; struct { u8 low; u8 high; } bytes; } CoordinateOutput;
typedef struct { CoordinateOutput first; CoordinateOutput second; } LocalBytes;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 get_entity_effect_value();             /* extern */

/* Updates the object's coordinates when a target passes the checks and new coordinates are found. */
s32 update_object_coordinates_if_valid(SpriteFrameState *object, EntityRec *context) {
    LocalBytes next_coords;
    s32 target;

    target = find_eligible_actor_at_tile_and_height(context, object->unk_24, object->unk_25, context->unk_88);
    if (target != 0) {
        if ((get_entity_effect_value(target, 0x1B) << 0x10) == 0) {
            if ((find_valid_nearby_position(context, object->unk_24, object->unk_25, &next_coords.first.coordinate, &next_coords.second.coordinate)
                << 0x10) != 0) {
                object->unk_24 = next_coords.first.bytes.low;
                object->unk_25 = next_coords.second.bytes.low;
                return 1;
            }
            return 2;
        }
    }
    return 0;
}
#include "modules/dungeon_engine_tile_map_fragment_b5d50.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/object_node.h"




extern void zero_words(void *, s32);
extern s32 ratan2(s32, s32);
extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 get_actor_height_difference(void *, void *);
extern s32 is_map_coordinate_out_of_bounds(s32, s32);
extern s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);

static __inline__ s16 offset_tile(u16 center, u16 offset)
{
    return center + offset;
}

/* Find an unoccupied valid position at the target or within two tiles. */
s32 find_valid_nearby_position(u8 *entry, s16 target_x, s16 target_y, s16 *out_x, s16 *out_y) {
    u16 tile_flags;
    u8 *occupied;
    u16 search_seed;
    u8 *actor;
    s32 near_x;
    u8 *object;
    s32 object_x;
    s32 object_y;
    u16 *near_dx;
    u16 *near_dy;
    u16 *far_dx;
    u16 *far_dy;
    s32 result_dx;
    s32 result_dy;
    s32 near_offset_x;
    s32 near_offset_y;
    s32 far_offset_x;
    s32 far_offset_y;
    s32 tile_offset_x;
    s32 tile_offset_y;
    s32 delta_x;
    s32 delta_y;
    s32 tile_distance;
    s32 separation;
    s32 y_distance;
    s16 slot;
    s32 near_dir;
    s32 far_dir;
    s16 attempts;
    s32 center_x;
    s32 center_y;
    s32 far_x;
    s32 far_y;
    s32 wrap_pending;
    s16 wrap_check;

    occupied = (u8 *)0x1F800000;
    if (entry != 0) {
        actor = entry;
        wrap_pending = 0;
    } else {
        actor = ((u8 *)dungeon_actor_ring_anchor);
        wrap_pending = 1;
        entry = *(u8 **)(actor + 88) + 32;
    }
    zero_words(occupied, 7);
    entry = *(u8 **)(entry + 92) + 32;
    while (entry != actor || (wrap_check = wrap_pending) != 0) {
        object = *(u8 * *)&((ObjectNodeHeader *)((u8 *)entry - 0x20))->sprite;
        object_x = *(u8 *)(object + 36);
        object_y = *(u8 *)(object + 37);
        delta_x = (s16)target_x - object_x;
        tile_distance = __builtin_abs(delta_x);
        delta_y = (s16)target_y - object_y;
        y_distance = __builtin_abs(delta_y);
        wrap_pending = 0;
        if (tile_distance < y_distance) {
            tile_distance = y_distance;
        }
        if (tile_distance < 3) {
            if (tile_distance == 0) {
                slot = 0;
            } else if (tile_distance == 1) {
                slot = (((ratan2(object_y - (s16)target_y, object_x - (s16)target_x) + 256) >> 9) & 7) + 1;
            } else {
                slot = (((ratan2(object_y - (s16)target_y, object_x - (s16)target_x) + 128) >> 8) & 15) + 9;
            }
            separation = (s16)get_actor_height_difference(actor, entry);
            if (separation < 0) {
                separation = -separation;
            }
            if (separation < 64) {
                *(u8 *)((u32)slot | (u32)occupied) = 1;
            }
        }

        entry = *(u8 **)(entry + 92) + 32;
    }

    if (occupied[0] == 0) {
        center_x = (s16)target_x;
        center_y = (s16)target_y;
        if ((is_map_coordinate_out_of_bounds(center_x, center_y) == 0) &&
            ((get_offset_map_cell_value_and_flags((s16)(target_x - 1), center_y, 0, &tile_flags) << 16) != 0) &&
            ((tile_flags & 0x8000) == 0) &&
            ((tile_flags & 0x400) == 0 || (*(u32 *)(entry + 28) & 0x40000) != 0) &&
            ((s16)sample_terrain_surface_height((((center_x << 6) + 32) & 0xffe0), (((center_y << 6) + 32) & 0xffe0),
                           (s16)(*(u16 *)(actor + 136) - 32)) < 512)) {
            *out_x = target_x;
            *out_y = target_y;
            return 1;
        }
    }

    attempts = 0;
    near_x = (s16)target_x;
    search_seed = g_dungeon_status.turn_counter;
    far_x = (s16)target_y;
    slot = search_seed & 7;
    do {
        near_dir = slot;
        if (*(occupied + near_dir + 1) == 0) {
            near_dx = dir_step_x + near_dir;
            near_dy = dir_step_y + near_dir;
            if ((near_offset_x = near_dx[0], near_offset_y = near_dy[0],
                 is_map_coordinate_out_of_bounds((s16)(target_x + near_offset_x), (s16)(target_y + near_offset_y))) == 0 &&
                (get_offset_map_cell_value_and_flags(near_x, far_x, near_dir, &tile_flags) << 16) != 0 &&
                (tile_flags & 0x8000) == 0 &&
                ((tile_flags & 0x400) == 0 || (*(u32 *)(entry + 28) & 0x40000) != 0) &&
                (s16)sample_terrain_surface_height((((near_x + (s16)near_dx[0]) << 6) + 32) & 0xffe0,
                                   (((far_x + (s16)near_dy[0]) << 6) + 32) & 0xffe0,
                                   (s16)(*(u16 *)(actor + 136) - 32)) < 512) {
                s16 near_result_x, near_result_y;
                near_result_x = near_dx[0];
                *out_x = target_x + near_result_x;
                near_result_y = near_dy[0];
                *out_y = target_y + near_result_y;
                return 1;
            }
        }
        attempts++;
        slot = (slot + 1) & 7;
    } while (attempts < 8);

    attempts = 0;
    far_x = (s16)target_x;
    search_seed = g_dungeon_status.turn_counter;
    far_y = (s16)target_y;
    near_dy = search_seed & 15;
    slot = near_dy;
    do {
        far_dir = slot;
        if (*(occupied + far_dir + 9) == 0) {
            far_dx = outer_ring_dx + far_dir;
            far_dy = outer_ring_dy + far_dir;

            if ((far_offset_x = far_dx[0], far_offset_y = far_dy[0],
                 is_map_coordinate_out_of_bounds(offset_tile(target_x, far_offset_x), offset_tile(target_y, far_offset_y))) == 0 &&
                ((tile_offset_x = far_dx[0], tile_offset_y = far_dy[0],
                  get_offset_map_cell_value_and_flags((s16)(target_x + tile_offset_x - 1), (s16)(target_y + tile_offset_y), 0, &tile_flags))
                      << 16) != 0 &&
                (tile_flags & 0x8000) == 0 &&
                ((tile_flags & 0x400) == 0 || (*(u32 *)(entry + 28) & 0x40000) != 0) &&
                (s16)sample_terrain_surface_height((((far_x + (s16)far_dx[0]) << 6) + 32) & 0xffe0,
                                   (((far_y + (s16)far_dy[0]) << 6) + 32) & 0xffe0,
                                   (s16)(*(u16 *)(actor + 136) - 32)) < 512) {
                result_dx = far_dx[0];
                *out_x = target_x + result_dx;
                result_dy = far_dy[0];
                *out_y = target_y + result_dy;
                return 1;
            }
        }
        attempts++;
        slot = (slot + 1) & 15;
    } while (attempts < 16);
    return 0;
}

#include "shared/actor_status_flags.h"
#include "dungeon/level/tile_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;

typedef struct {
    u8 first;
    u8 second;
    u8 unk_02[10];
} DungeonRecord;

extern u8 temporary_item_record[];
extern u8 held_item_record[];
extern DungeonRecord dungeon_ground_item_positions[];

extern s16 find_table_value_index(DungeonItemEntry *);
extern void compact_item_entry_table(s16);
extern s16 get_bounded_stride_index(s32 *, u8 *, s32, s32);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);

/* Clears a slot and updates its associated entry or dungeon state. */
void clear_slot_and_update_linked_state(DungeonItemEntry *slot) {
    s16 lookup_result;
    if (slot != 0) {
        *(s32 *)slot = 0;
        lookup_result = find_table_value_index(slot);
        if (lookup_result >= 0) {
            compact_item_entry_table(lookup_result);
            return;
        }
        if ((u8 *)slot == held_item_record) {
            ActorRecord *state = dungeon_actor_ring_anchor;
            ((PlayerRecord *)state)->unk_124 = 0;
            state->flags1C &= ACTOR_CARRYING_CLEAR_MASK;
            return;
        }
        if ((u8 *)slot == temporary_item_record || slot == ((PlayerRecord *)dungeon_actor_ring_anchor)->selected_floor_entry) {
            s16 record_index;
            *(s32 *)temporary_item_record = 0;
            record_index = get_bounded_stride_index(((s32 *)((PlayerRecord *)dungeon_actor_ring_anchor)->selected_floor_entry), ((u8 *)dungeon_ground_items), 4, 0x40);
            if (record_index >= 0) {
                update_map_cell_flags_with_item_limit(dungeon_ground_item_positions[record_index].first, dungeon_ground_item_positions[record_index].second, TILE_HAS_ITEM);
            }
            *(s32 *)((PlayerRecord *)dungeon_actor_ring_anchor)->selected_floor_entry = 0;
        }
    }
}

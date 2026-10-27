#include "shared/dungeon_item_entries.h"
#include "shared/entity.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/player/item.h"
#include "dungeon/actor/status.h"
#include "dungeon/system.h"
#include "dungeon/item/message.h"

extern s32 process_record_and_update_linked_state();
extern void create_type_212_object(s32 flag, s8 value);
extern void refresh_packed_grid_nibbles(void);
extern s32 mark_active_nodes_by_callback();
extern void clear_slot_and_update_linked_state(DungeonItemEntry *slot);

extern u8 dungeon_ground_item_positions[];
extern u8 floor_objects[];
extern u8 dungeon_floor_object_positions[];
extern u8 D_800E1863;
extern u8 floor_trap_update_address[];

#define U8(p, o)  (*(u8  *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Apply a target effect and clear dungeon entities and tiles when requested. */
s32 flatten_floor_terrain(void *target, DungeonItemEntry *effect_arg, s16 effect_id, s32 context) {
    s32 *dungeon_state = ((s32 *)(&g_game_work));
    u8 *grid_info;
    s32 grid_base;
    void *entity;
    void *first_entity;
    u8 *entry_data;
    u8 *entry_flags;
    s32 x;
    s32 y;
    s32 cell_index;
    s32 cleared_tile;
    s32 clear_mask;
    s32 effect_counter;
    s32 effect_code;
    u16 *cell;

    grid_info = (u8 *) (dungeon_state + 119);
    grid_base = dungeon_state[119];
    effect_code = effect_id;
    if (effect_code == 13) {
        return process_record_and_update_linked_state(effect_arg, context);
    }
    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = effect_arg;
        begin_mode_selected_item_action(target, &view_reference_entity, &reference_tile_object, target);
        return 0;
    }
    if ((u32) target <= 0x9FFFFFFFU) {
        display_actor_item_status_message(target, effect_arg);
        if (feed_actor_restore_mp(target, U16(((u8 *)entity_action_selectors), U8(target, 0x13) * 2) & 3, effect_arg) == 0) {
            place_actor_item(target, effect_arg);
            return 1;
        }
    } else if (dungeon_floor_flags & 0x20000000) {
        create_type_212_object(1, 8);
        play_sound_if_enabled(0x80F);
        entity = dungeon_actor_ring_anchor;
        first_entity = entity;
        do {
            S16(entity, 0x88) = 0;
            S32(entity, 0x1C) = S32(entity, 0x1C) | 0x40000000;
            entity = (void *) (S32(entity, 0x5C) + 0x20);
        } while (entity != first_entity);
        entry_data = dungeon_ground_item_positions;
        entry_flags = ((u8 *)dungeon_ground_items);
        for (effect_counter = 0; effect_counter < 0x40; effect_counter++) {
            if (U8(entry_flags, effect_counter * 4 + 1) != 0) {
                S16(entry_data, effect_counter * 0xC + 4) = 0;
            }
        }
        entry_data = dungeon_floor_object_positions;
        entry_flags = floor_objects;
        for (effect_counter = 0; effect_counter < 0x20; effect_counter++) {
            if (U8(entry_flags, effect_counter * 4 + 1) != 0) {
                S16(entry_data, effect_counter * 0x18 + 0x12) = 0;
            }
        }
        y = 1;
        cleared_tile = 0x68;
        do {
            x = 1;
            do {
                cell = (u16 *) ((x + (y << S16(grid_info, 0x14))) * 6 + grid_base);
                if (*cell >= 0xBU) {
                    *cell = cleared_tile;
                    cell = (u16 *) ((x + (y << S16(grid_info, 0x14))) * 6 + grid_base);
                    U16(cell, 4) = U16(cell, 4) & 0x7B32;
                }
                cell_index = x + (y << S16(grid_info, 0x14));
                x += 1;
                U16((u16 *) (cell_index * 6 + grid_base), 2) = 0;
            } while (x < 0x3F);
            y += 1;
        } while (y < 0x3F);
        refresh_packed_grid_nibbles();
        clear_mask = 0x3FF7FFFF;
        dungeon_floor_flags = dungeon_floor_flags & clear_mask;
        mark_active_nodes_by_callback(floor_trap_update_address);
    } else {
        display_formatted_context_message(&D_800E1863);
    }
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    clear_slot_and_update_linked_state(effect_arg);
    return 1;
}

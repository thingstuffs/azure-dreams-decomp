#include "shared/item_ids.h"
/* dispatch_dungeon_category_action (dungeon overlay) -- MATCHES at gcc 2.8.1 (words_off=0).
 * s32-returning; the r<0 path does `func_80098B10(); return -1;`. gcc emits a
 * dead `j $Lepi` with the `li v0,-1` return-value setup in ITS delay slot; the
 * sibcall `jal func_80098B10` (member of config/sibcall_syms.dungeon.txt) is
 * left as jal because that delay is non-nop. maspsx LEAD-22 SHAPE C relocates
 * the `li v0,-1` into the converted `j func_80098B10` delay slot, matching
 * retail (`j 0x98b10 / li v0,-1`). Config: 2.8.1.
 */
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/player.h"


extern u32 *dungeon_category_action_handlers[];
extern u8 floor_objects[];

extern s16 get_special_table_data_index(void *);
extern void process_unflagged_linked_entries(s32);
extern void process_unflagged_linked_entries_alt(s32);
extern s32 find_entry_at_tile_coordinates(s16 x, s16 y, s16 z);
extern void call_slot_handler_and_update_status(s32 handler_id, void *object_ptr, s32 slot_id, s8 update_state);
extern void allocate_object_at_coordinates(void *, void *, s16);
extern void func_800BCFBC(s32, u32, s32);

/* Dispatches an action handler after processing special cases and updating dungeon state. */
s32 dispatch_dungeon_category_action(void *actor, void *action, s16 dispatch_mode, s32 handler_param) {
    s32 action_index;
    s32 type_index;
    u32 handler_entry;
    u32 handler_tag;
    s16 result;
    void *linked_entity;
    void (*handler)(void *, void *, s16, s32);

    if (*((u8 *)action + 1) == ITEM_KIND_EGG) {
        if ((s16)dispatch_mode != 0x15) {
            allocate_object_at_coordinates(actor, action, dispatch_mode);
            return;
        }
    }
    type_index = *((u8 *)action + 1) - 1;
    action_index = *((u8 *)action + 0) - 1;
    if (*((u8 *)action + 1) == ITEM_KIND_TRAP) {
        linked_entity = *(void **)((u8 *)actor - 0x14);
        result = find_entry_at_tile_coordinates(*((u8 *)linked_entity + 0x24), *((u8 *)linked_entity + 0x25),
            *((s16 *)((u8 *)actor + 0x88)));
        if (result < 0) {
            return -1;
        }
        call_slot_handler_and_update_status(floor_objects[result * 4], actor, result, 1);
        return;
    }
    g_dungeon_status.activity_counts.parts.pending_action_count += 1;
    handler_entry = dungeon_category_action_handlers[type_index][action_index];
    handler_tag = handler_entry >> 0x18;
    handler = (void (*)(void *, void *, s16, s32))((handler_entry & 0xFFFFFF) | 0x80000000);
    if (handler_tag != 0) {
        func_800BCFBC(handler_tag - 1, handler_tag, action_index);
    }
    if ((s16)dispatch_mode != 0x15) {
        if (reference_tile_object.secondary_item == 0) {
            result = get_special_table_data_index(action);
            if (result != 0x15) {
                if (result == 0x16) {
                    *(*(s32 **)((u8 *)dungeon_actor_ring_anchor + 0xF0)) = 0;
                } else {
                    clear_player_linked_action_flags();
                }
            }
        }
    }
    if ((s16)dispatch_mode == 0x15) {
        process_unflagged_linked_entries_alt(*(s32 *)((u8 *)dungeon_actor_ring_anchor + 0x5C));
        process_unflagged_linked_entries(*(s32 *)((u8 *)dungeon_actor_ring_anchor + 0x5C));
        g_dungeon_status.flags |= 0x812;
    }
    handler(actor, action, dispatch_mode, handler_param);
}

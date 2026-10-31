#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/player.h"
extern s32 *dungeon_category_action_handlers[];

/* Runs a banked callback and advances the object state when it completes. */
void advance_banked_category_action(ActorRecord *object, void *unused_1, void *unused_2, ActorRecord *context) {
    u8 *callback_data;
    u8 state;
    s32 **callback_table;
    s32 *callback_row;
    u32 row_index;
    u32 entry_index;
    u32 callback_entry;
    u32 bank;
    s32 (*callback)(s32, void *, s32, s32);

    state = object->action_phase.u;
    if (state == 0 || state == 16) {
        callback_data = *(u8 **)((u8 *)object + 0x110);
        row_index = callback_data[1] - 1;
        entry_index = callback_data[0] - 1;
        callback_table = dungeon_category_action_handlers;
        callback_row = callback_table[row_index];
        callback_entry = (u32)callback_row[entry_index];
        bank = callback_entry >> 0x18;
        callback = (s32 (*)(s32, void *, s32, s32))((callback_entry & 0xFFFFFF) | 0x80000000);
        if (bank != 0) {
            func_800BCFBC(--bank);
        }
        if (callback((s32)context | 0xA0000000, callback_data, 0, 0) != 0) {
            *(void **)((u8 *)object + 0x110) = 0;
            object->action_phase.u += 1;
            return;
        }
        return;
    }
    if (state == 1) {
        process_unflagged_linked_entries_alt(context->next_actor_header);
        process_unflagged_linked_entries(context->next_actor_header);
        g_dungeon_status.flags |= 0x812;
        restore_player_control_callback(object, context);
    }
}

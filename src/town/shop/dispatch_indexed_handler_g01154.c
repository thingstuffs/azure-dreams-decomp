/* Dispatch indexed handler g01154.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01154 - CL:town/func_800B47B0, CL:town/func_800B47E8.
 */
#include "town/shop/dispatch_indexed_handler_g01154.h"

/* Call the indexed dispatch handler with its table entry. */
void dispatch_indexed_handler(void *context, s32 handler_index) {
    DispatchFunc *dispatch_table;
    DispatchFunc *handler_entry;

    dispatch_table = D_800D1638;
    handler_entry = dispatch_table + handler_index;
    (*handler_entry)(context, (void *)handler_entry);
}

/* Call the indexed dispatch handler with its table entry. */
void dispatch_indexed_handler_alt(void *context, s32 handler_index) {
    DispatchFunc *dispatch_table;
    DispatchFunc *handler_entry;

    dispatch_table = D_800D1640;
    handler_entry = dispatch_table + handler_index;
    (*handler_entry)(context, (void *)handler_entry);
}

/* Update the active entry index and notify handlers when its index or ten-entry group changes. */
void update_active_entry_and_notify_handlers(s8 *state, s32 input) {
    s32 active_slot;
    s32 group_slot;
    s32 index_result;
    s32 next_group;
    s32 next_index;
    S_800B1F80_1 *entry;

    entry = state + ((((Rec_func_800B1DCC_arg0 *)state)->unk_0C * 0x10) + 0x1C);
    index_result = advance_index_with_directional_clamp(entry->unk_08, input, entry->unk_0C);
    next_index = index_result;
    if (next_index >= entry->unk_0C) {
        entry->unk_08 = 0;
        return;
    }
    if (next_index != entry->unk_08) {
        entry->unk_08 = next_index;
        active_slot = ((Rec_func_800B1DCC_arg0 *)state)->unk_0C;
        next_group = index_result / 10;
        dispatch_indexed_handler_alt((void *)*((s32 *)((s8 *)state + (active_slot * 4))), active_slot);
        if (next_group != entry->unk_00) {
            entry->unk_00 = next_group;
            group_slot = ((Rec_func_800B1DCC_arg0 *)state)->unk_0C;
            dispatch_indexed_handler((void *)*((s32 *)((s8 *)state + (group_slot * 4))), group_slot);
        }
    }
}

/* Decrement the selected entry value, update its quotient, and invoke entry callbacks. */
void decrement_entry_and_notify_handlers(void *state) {
    s32 selected_index;
    s32 refresh_index;
    s32 related_index;
    s32 updated_value;
    S_800B2068_1 *entry;

    entry = state + ((((Rec_func_800B1DCC_arg0 *)state)->unk_0C * 0x10) + 0x1C);
    updated_value = advance_index_with_directional_clamp(entry->unk_08 - 1, 1, entry->unk_0C);
    entry->unk_08 = updated_value;
    entry->unk_00 = (s32) (updated_value / 10);
    selected_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_0C;
    dispatch_indexed_handler_alt((void *)(*((s32 *)state + selected_index)), selected_index);
    refresh_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_0C;
    dispatch_indexed_handler((void *)(*((s32 *)state + refresh_index)), refresh_index);
    related_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_18;
    dispatch_indexed_handler((void *)(*((s32 *)state + related_index)), related_index);
}

/* Dispatch indexed handler g01154.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800B47B0, CL:town/func_800B47E8.
 */
#include "town/shop/dispatch_indexed_handler_g01154.h"
#include "town/shop/resource_entry_initialization_g01156.h"
#include "town/shop.h"

/* Call the indexed dispatch handler with its table entry. */
void dispatch_indexed_handler(struct ObjectNodeHeader *node, s32 handler_index) {
    DispatchFunc *dispatch_table;
    DispatchFunc *handler_entry;

    dispatch_table = D_800D1638;
    handler_entry = dispatch_table + handler_index;
    (*handler_entry)(node);
}

/* Call the indexed dispatch handler with its table entry. */
void dispatch_entry_change_handler(struct ObjectNodeHeader *node, s32 handler_index) {
    DispatchFunc *dispatch_table;
    DispatchFunc *handler_entry;

    dispatch_table = D_800D1640;
    handler_entry = dispatch_table + handler_index;
    (*handler_entry)(node);
}

/* Update the active entry index and notify handlers when its index or ten-entry group changes. */
void update_active_entry_and_notify_handlers(ItemMenuInputObject *state, s32 input) {
    ObjectNodeHeader **nodes = (ObjectNodeHeader **)state;
    s32 active_slot;
    s32 group_slot;
    s32 index_result;
    s32 next_group;
    s32 next_index;
    TownGroupIndex *entry;

    entry = &state->groups[state->preset];
    index_result = advance_index_with_directional_clamp(entry->selection, input, entry->value);
    next_index = index_result;
    if (next_index >= entry->value) {
        entry->selection = 0;
        return;
    }
    if (next_index != entry->selection) {
        entry->selection = next_index;
        active_slot = state->preset;
        next_group = index_result / 10;
        dispatch_entry_change_handler(nodes[active_slot], active_slot);
        if (next_group != entry->page) {
            entry->page = next_group;
            group_slot = state->preset;
            dispatch_indexed_handler(nodes[group_slot], group_slot);
        }
    }
}

/* Decrement the selected entry value, update its quotient, and invoke entry callbacks. */
void decrement_entry_and_notify_handlers(ItemMenuInputObject *state) {
    ObjectNodeHeader **nodes = (ObjectNodeHeader **)state;
    s32 selected_index;
    s32 refresh_index;
    s32 related_index;
    s32 updated_value;
    TownGroupIndex *entry;

    entry = &state->groups[state->preset];
    updated_value = advance_index_with_directional_clamp(entry->selection - 1, 1, entry->value);
    entry->selection = updated_value;
    entry->page = (s32) (updated_value / 10);
    selected_index = state->preset;
    dispatch_entry_change_handler(nodes[selected_index], selected_index);
    refresh_index = state->preset;
    dispatch_indexed_handler(nodes[refresh_index], refresh_index);
    related_index = state->destination_index;
    dispatch_indexed_handler(nodes[related_index], related_index);
}

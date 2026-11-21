#include "town/scene/record_actions.h"
#include "town.h"

s32 forward_context_request_to_handler_b(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    return apply_selected_entry_values(entry, entry_index);
}

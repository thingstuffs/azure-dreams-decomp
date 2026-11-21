#include "town/scene/record_actions.h"
#include "town/scene/hooks.h"

s32 forward_data_and_value_b(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    return apply_selected_entry_values(entry, entry_index);
}

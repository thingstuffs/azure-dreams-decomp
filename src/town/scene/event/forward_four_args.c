#include "town/scene/entry_requests.h"
#include "town/scene/record_actions.h"

s32 forward_scene_request_arguments(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    return apply_selected_entry_values(entry, entry_index);
}

#include "town/scene/record_actions.h"
#include "town.h"
#include "town/scene.h"

s32 forward_context_request_to_handler_b(TownObjectSet *entry, s32 entry_index) {
    return apply_selected_entry_values(entry, entry_index);
}

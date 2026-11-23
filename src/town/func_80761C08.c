#include "town/scene/record_actions.h"
#include "town/scene.h"

s32 forward_selected_entry_values(TownObjectSet *row, s32 entry_index) {
    return apply_selected_entry_values(row, entry_index);
}

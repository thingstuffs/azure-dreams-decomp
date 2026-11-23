#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"

/* Passes context and entry_index to process_checked_entry. */
void forward_to_process_checked_entry(TownObjectSet *context, s32 entry_index) {
    process_checked_entry(context, entry_index);
}

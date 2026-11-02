#include "common.h"
#include "town/scene/object.h"
#include "town/scene.h"

void select_handler_by_state_code_0x798(s32 slotIndex);

/* Pass the result of func_80017BBC(0xD, 2) to release_object_and_compact_slot_list. */
void release_object_slot_d_2(void) {
    select_handler_by_state_code_0x798(find_entry_index_by_grid_bytes(0xD, 2));
}

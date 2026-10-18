#include "common.h"

void initialize_templated_state_and_position(s32, s32, s32, s32, s32); /* extern */
void initialize_panel_content_and_positions(s32); /* extern */
void store_pair_values(s32, s32); /* extern */

/* Set up the object, update its embedded records, and finalize it. */
void build_owned_floating_number_widget(s32 object_addr, s32 setup_value, s32 update_value_1, s32 update_value_2) {
    store_pair_values(object_addr, setup_value);
    initialize_templated_state_and_position(object_addr + 0x38, object_addr + 0x10, object_addr + 0x20, update_value_1, update_value_2);
    initialize_panel_content_and_positions(object_addr);
}

#include "common.h"

extern short scene_sprite_y_history[64];
extern short scene_sprite_x_history[64];

/* Initializes the two 64-entry tables to 0x500 and 0x380. */
void initialize_runtime_table_defaults(void) {
    int entry_index;

    for (entry_index = 0x3F; entry_index >= 0; entry_index--) {
        scene_sprite_x_history[entry_index] = 0x500;
        scene_sprite_y_history[entry_index] = 0x380;
    }
}

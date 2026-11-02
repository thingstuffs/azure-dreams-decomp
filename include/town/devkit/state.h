#ifndef TOWN_DEVKIT_STATE_H
#define TOWN_DEVKIT_STATE_H
/* Prototypes of the functions defined in src/town/devkit/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* shop_check_selected_entry_state.c */
s32 get_selected_flag_state(s32 unused_selection);

/* shop_set_entry_step_flag.c */
void set_entry_bit_flag(s32 row_index, s32 entry_index);

/* shop_update_availability_flag.c */
void update_combined_flag(void);

#endif

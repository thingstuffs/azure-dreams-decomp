#ifndef SHARED_TOWN_HANDLER_ENTRIES_H
#define SHARED_TOWN_HANDLER_ENTRIES_H
#include "shared/action_handler_tables_data.h"

/* dispatch_selected_entry_if_nonzero indexes 32-bit entries by the
 * record selector and tests for zero. The table extent is not established. */
extern int approach_action_handler_table[];
extern int D_800D0098[];
extern int type_three_action_handler_table[];
extern int target_move_direction_frames[];
extern int D_800D00B0[];
extern int ground_action_direction_frames[];
extern int countdown_expiry_direction_frames[];
extern int D_800D0108[];
extern int D_800D0110[];
extern int counted_action_handler_table[];
extern int D_800D0130[];
extern int D_800D0140[];
extern int target_countdown_direction_frames[];
extern int reset_countdown_direction_frames[];
extern int D_800D01A0[];
extern int target_action_direction_frames[];

#endif

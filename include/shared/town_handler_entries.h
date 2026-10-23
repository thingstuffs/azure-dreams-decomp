#ifndef SHARED_TOWN_HANDLER_ENTRIES_H
#define SHARED_TOWN_HANDLER_ENTRIES_H

/* call_the_handler_selects_nonzero_entry indexes 32-bit entries by the
 * record selector and tests for zero. The table extent is not established. */
extern int approach_action_handler_table[];
extern int movement_action_handler_table[];
extern int D_800D0098[];
extern int type_three_action_handler_table[];
extern int D_800D00A8[];
extern int D_800D00B0[];
extern int action_object_handler_table[];
extern int D_800D00D0[];
extern int D_800D00E0[];
extern int D_800D0108[];
extern int D_800D0110[];
extern int counted_action_handler_table[];
extern int D_800D0130[];
extern int countdown_action_handler_table[];
extern int D_800D0140[];
extern int D_800D0170[];
extern int D_800D0180[];
extern int D_800D01A0[];
extern int D_800D01E0[];

#endif

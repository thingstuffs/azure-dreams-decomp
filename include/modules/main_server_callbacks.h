#ifndef MODULES_MAIN_SERVER_CALLBACKS_H
#define MODULES_MAIN_SERVER_CALLBACKS_H

#include "common.h"

/* D_80020034 / D_80020048: event index zero is null; indices 1..4
 * receive no arguments and return the next card operation status. */
typedef s32 (*card_event_callback_fn)(void);

s32 card_advance_selected_operation(void);
s32 card_boot_poll_state_two_transition(void);
s32 card_boot_reset_operation_return_five(void);
s32 consume_pending_event_flag(void);
s32 card_poll_selected_operation_state(void);

#endif

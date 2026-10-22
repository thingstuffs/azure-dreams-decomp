#ifndef FRONTEND_CARD_EVENT_CALLBACKS_H
#define FRONTEND_CARD_EVENT_CALLBACKS_H

#include "common.h"

/* Memory-card event action called without arguments; returns the dispatcher result. */
typedef s32 (*card_dev_event_callback_fn)(void);

/* Five-entry memory-card event dispatch table stored in overlay data.
 * card_devkit_dispatch_polled_event copies the table and calls the nonzero polled-event selection. */
typedef struct card_dev_event_table {
    card_dev_event_callback_fn slot[5]; /* event-code-indexed callbacks; event code zero is skipped by the dispatcher */
} card_dev_event_table;

extern card_dev_event_table D_80400054;
extern card_dev_event_table D_80400068;
s32 advance_processing_selected_slot_sets_completion_flag(void);
s32 card_dev_clear_op_failed(void);
s32 card_dev_clear_op_busy(void);
s32 process_selection(void);
s32 card_dev_advance_boot_step(void);

#endif

#ifndef FRONTEND_CARD_EVENT_CALLBACKS_H
#define FRONTEND_CARD_EVENT_CALLBACKS_H

#include "common.h"

typedef s32 (*card_dev_event_callback_fn)(void);

typedef struct card_dev_event_table {
    card_dev_event_callback_fn slot[5];
} card_dev_event_table;

extern card_dev_event_table D_80400054;
extern card_dev_event_table D_80400068;
s32 advance_processing_selected_slot_sets_completion_flag(void);
s32 card_dev_clear_op_failed(void);
s32 card_dev_clear_op_busy(void);
s32 process_selection(void);
s32 card_dev_advance_boot_step(void);

#endif

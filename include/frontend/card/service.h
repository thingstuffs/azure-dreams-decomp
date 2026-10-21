#ifndef FRONTEND_CARD_SERVICE_H
#define FRONTEND_CARD_SERVICE_H
/* Prototypes of the functions defined in src/frontend/card/service/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* advance_processing_selected_slot_sets_completion_flag.c */
s32 advance_processing_selected_slot_sets_completion_flag(void);

/* build_entry_list.c */
s32 build_entry_list(void);

/* card_dev_cache_save_header.c */
void card_dev_cache_save_header(s32 entry_index, void *source);

/* card_dev_run_selected_operation.c */
s32 card_dev_run_selected_operation(s32 card_index);

/* card_dev_run_slot_operation.c */
s32 card_dev_run_slot_operation(s32 slot_index);

/* card_devkit_debounce_channel_status.c */
s32 *card_devkit_debounce_channel_status(void);

/* card_devkit_dispatch_polled_event.c */
s32 card_devkit_dispatch_polled_event(void);

/* card_devkit_has_directory_name_prefix.c */
s32 card_devkit_has_directory_name_prefix(s32 count, u8 *text);

/* card_devkit_poll_first_software_event.c */
s32 card_devkit_poll_first_software_event(void);

/* card_devkit_poll_stable_slot_state.c */
s32 card_devkit_poll_stable_slot_state(void);

/* process_selection.c */
s32 process_selection(void);

/* read_and_update_indexed_record.c */
s32 read_and_update_indexed_record(s32 index, void *data_ptr);

#endif

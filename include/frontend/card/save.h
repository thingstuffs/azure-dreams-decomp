#ifndef FRONTEND_CARD_SAVE_H
#define FRONTEND_CARD_SAVE_H
/* Prototypes of the functions defined in src/frontend/card/save/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_func_804061C4_0;

/* advance_indexed_object_operation.c */
void advance_indexed_object_operation(void *inputPtr);

/* card_devkit_build_save_slot_windows.c */
void card_devkit_build_save_slot_windows(void *ptr);

/* card_devkit_refresh_save_slot_pair_highlights.c */
void card_devkit_refresh_save_slot_pair_highlights(void *ptr);

/* card_devkit_refresh_save_slot_selection.c */
void card_devkit_refresh_save_slot_selection(void *menu);

/* complete_object_operation.c */
void complete_object_operation(void *context);

/* handle_object_menu_input.c */
void handle_object_menu_input(void *menu);

/* invoke_callback_with_zero.c */
void invoke_callback_with_zero(void *record_data);

/* process_five_object_entries.c */
void process_five_object_entries(struct S_func_804061C4_0 *state);

/* process_object_entry_batch.c */
void process_object_entry_batch(void *ptr);

/* select_object_callback_by_entry.c */
void select_object_callback_by_entry(void *object_state);

#endif

#ifndef FRONTEND_CARD_SAVE_H
#define FRONTEND_CARD_SAVE_H
/* Prototypes of the functions defined in src/frontend/card/save/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_func_804061C4_0;

/* card_dev_create_save_screen.c */
struct CardSaveScreenState;
struct CardSaveScreenState *card_dev_create_save_screen(s32 init_value);

/* select_save_slot_callback.c */
void select_save_slot_callback(void *inputPtr);

/* card_devkit_build_save_slot_windows.c */
void card_devkit_build_save_slot_windows(void *ptr);

/* card_devkit_refresh_save_slot_pair_highlights.c */
void card_devkit_refresh_save_slot_pair_highlights(void *ptr);

/* card_devkit_refresh_save_slot_selection.c */
void card_devkit_refresh_save_slot_selection(void *menu);

/* finish_save_slot_check.c */
void finish_save_slot_check(void *context);

/* handle_object_menu_input.c */
void handle_object_menu_input(void *menu);

/* refresh_save_slot_selection_and_resume_menu_input.c */
void refresh_save_slot_selection_and_resume_menu_input(void *record_data);

/* finish_save_slot_operation.c */
void finish_save_slot_operation(struct S_func_804061C4_0 *state);

/* commit_save_and_refresh_slots.c */
void commit_save_and_refresh_slots(void *ptr);

/* select_slot_menu_callback.c */
void select_slot_menu_callback(void *object_state);

#endif

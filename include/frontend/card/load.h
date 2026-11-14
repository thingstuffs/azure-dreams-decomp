#ifndef FRONTEND_CARD_LOAD_H
#define FRONTEND_CARD_LOAD_H
/* Prototypes of the functions defined in src/frontend/card/load/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_func_80406AA8_0;

/* card_devkit_highlight_selected_load_slot.c */
void card_devkit_highlight_selected_load_slot(void *ptr);

/* handle_menu_selection_input.c */
void handle_menu_selection_input(void *object);

/* init_save_header_buffer.c */
void init_save_header_buffer(short *dest, int index, int mode);

/* select_load_slot_callback.c */
void select_load_slot_callback(void *ptr);

/* resume_load_menu_input.c */
void resume_load_menu_input(void *ptr);

/* finish_load_slot_check.c */
void finish_load_slot_check(struct S_func_80406AA8_0 *state);

#endif

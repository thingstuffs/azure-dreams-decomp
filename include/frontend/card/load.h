#ifndef FRONTEND_CARD_LOAD_H
#define FRONTEND_CARD_LOAD_H
/* Prototypes of the functions defined in src/frontend/card/load/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_func_80406AA8_0;

/* card_devkit_highlight_selected_load_slot.c */
void card_devkit_highlight_selected_load_slot(void *ptr);

/* handle_menu_selection_input.c */
void handle_menu_selection_input(void *object);

/* initialize_destination_template_state.c */
void initialize_destination_template_state(short *dest, int index, int mode);

/* reset_menu_object_state.c */
void reset_menu_object_state(void *ptr);

/* reset_object_operation_state.c */
void reset_object_operation_state(void *ptr);

/* update_menu_object_state.c */
void update_menu_object_state(struct S_func_80406AA8_0 *state);

#endif

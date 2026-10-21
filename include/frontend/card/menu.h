#ifndef FRONTEND_CARD_MENU_H
#define FRONTEND_CARD_MENU_H
/* Prototypes of the functions defined in src/frontend/card/menu/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* card_boot_clear_menu_state.c */
void card_boot_clear_menu_state(void *ptr);

/* card_boot_handle_menu_selection_input.c */
void card_boot_handle_menu_selection_input(void *menu);

/* card_boot_initialize_menu_pointer.c */
void card_boot_initialize_menu_pointer(void *ptr);

/* card_boot_poll_status_and_select_context.c */
void card_boot_poll_status_and_select_context(void *state);

/* card_boot_update_object_state_and_callback.c */
void card_boot_update_object_state_and_callback(void *object_data);

/* menu.c */
void func_80020F40(void *record_data);

#endif

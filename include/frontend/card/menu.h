#ifndef FRONTEND_CARD_MENU_H
#define FRONTEND_CARD_MENU_H
/* Prototypes of the functions defined in src/frontend/card/menu/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "frontend/libcard/card_chooser.h"

/* card_boot_clear_menu_state.c */
void card_boot_clear_menu_state(CardChooserBody *menu);

/* card_boot_handle_menu_selection_input.c */
void card_boot_handle_menu_selection_input(CardChooserBody *menu);

/* card_boot_init_chooser_callback.c */
void card_boot_init_chooser_callback(CardChooserBody *ptr);

/* card_boot_poll_status_and_select_context.c */
void card_boot_poll_status_and_select_context(CardChooserBody *state);

/* card_boot_update_object_state_and_callback.c */
void card_boot_update_object_state_and_callback(CardChooserBody *object);

/* menu.c */
void decrement_card_menu_countdown(CardChooserBody *record_data);

/* card_dev_open_format_confirmation_dialog.c */
void card_dev_open_format_confirmation_dialog(CardChooserBody *menu);

/* card_dev_open_no_memory_card_dialog.c */
void card_dev_open_no_memory_card_dialog(CardChooserBody *menu);

/* card_dev_open_damaged_card_dialog.c */
void card_dev_open_damaged_card_dialog(CardChooserBody *menu);

#endif

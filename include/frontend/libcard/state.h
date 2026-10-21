#ifndef FRONTEND_LIBCARD_STATE_H
#define FRONTEND_LIBCARD_STATE_H
/* Prototypes of the functions defined in src/frontend/libcard/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* card_boot_poll_card_chooser_status.c */
void card_boot_poll_card_chooser_status(void *state);

/* card_boot_poll_status_and_dismiss_dialog.c */
void card_boot_poll_status_and_dismiss_dialog(void *record_data);

/* reset_menu_object_state.c */
void reset_menu_object_state_2(void *record_part);

#endif

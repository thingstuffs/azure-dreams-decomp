#ifndef FRONTEND_LIBCARD_STATE_H
#define FRONTEND_LIBCARD_STATE_H
/* Prototypes of the functions defined in src/frontend/libcard/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "frontend/libcard.h"

/* card_boot_poll_card_chooser_status.c */
void card_boot_poll_card_chooser_status(CardChooserBody *state);

/* card_boot_poll_status_and_dismiss_dialog.c */
void card_boot_poll_status_and_dismiss_dialog(Object_800128C8 *record_data);

/* card_boot_restore_chooser_mode.c */
void card_boot_restore_chooser_mode(CardChooserBody *menu);

void card_boot_enter_no_card_notice(CardChooserBody *chooser);

void card_boot_enter_damaged_card_notice(CardChooserBody *chooser);

void card_boot_enter_format_confirmation(CardChooserBody *state);

#endif

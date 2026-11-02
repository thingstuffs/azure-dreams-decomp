#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/message_dialog.h"


/* Calls the handler when the referenced record value is zero. */
void card_boot_close_dialog_when_response_clears(CardMessageDialogBody *record) {
    if (*record->result == 0) {
        card_boot_close_message_dialog(0);
    }
}

#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024FAC_0 {
    s32 * unk_00;
} S_80024FAC_0;   /* arg0 in card_boot_poll_status_and_dismiss_dialog; pointer addresses record offset 0x10 */


#include "modules/main_server_ship_interfaces.h"
s32 card_boot_close_message_dialog();                     /* extern */
void card_boot_restore_saved_selection_callback(void *);                            /* extern */
extern M2C_UNK D_8002593C;

/* Update the record and switch its table when the status reaches four. */
void card_boot_poll_status_and_dismiss_dialog(void *record_data) {
    card_boot_restore_saved_selection_callback(record_data);
    if (card_boot_debounce_card_status_events() >= 4) {
        card_boot_close_message_dialog(0);
        ((S_80024FAC_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_8002593C;
    }
}

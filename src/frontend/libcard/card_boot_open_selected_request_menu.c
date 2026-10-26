#include "common.h"
#include "m2c_compat.h"

#include "frontend/libcard.h"
#include "frontend/libcard/interfaces.h"
typedef struct S_80027528_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    void *request;
} S_80027528_0;   /* arg0 in card_boot_open_selected_request_menu */

/* Updates the record using its current mode and stored value. */
void card_boot_open_selected_request_menu(void *record) {
    s32 mode;

    card_boot_destroy_card_chooser(record - 0x20);
    mode = ((S_80027528_0 *)record)->unk_00;
    if (mode == 0) {
        card_boot_create_slot_selection_menu(((S_80027528_0 *)record)->request, 0);
        return;
    } else {
        card_boot_create_save_slot_menu(((S_80027528_0 *)record)->request, mode);
    }
}

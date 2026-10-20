#include "common.h"
#include "m2c_compat.h"

s32 card_boot_close_message_dialog(s32);                     /* extern */

typedef struct S_800226A8_0 {
    u8 pad_00[0x20];
    s32 * unk_20;
} S_800226A8_0;   /* arg0 in card_boot_close_dialog_when_response_clears */

/* Calls the handler when the referenced record value is zero. */
void card_boot_close_dialog_when_response_clears(S_800226A8_0 *record) {
    if (*record->unk_20 == 0) {
        card_boot_close_message_dialog(0);
    }
}

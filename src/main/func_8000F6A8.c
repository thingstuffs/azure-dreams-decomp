#include "common.h"
#include "m2c_compat.h"

s32 cardBootCloseMessageDialog();                     /* extern */

typedef struct S_800226A8_0 {
    u8 pad_00[0x20];
    s32 * unk_20;
} S_800226A8_0;   /* arg0 in cardBootCloseDialogWhenResponseClears */

/* Calls the handler when the referenced record value is zero. */
void cardBootCloseDialogWhenResponseClears(S_800226A8_0 *record) {
    if (*record->unk_20 == 0) {
        cardBootCloseMessageDialog(0);
    }
}

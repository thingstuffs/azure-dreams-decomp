#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"

typedef struct S_8001EEAC_0 {
    s32 * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_8001EEAC_0;   /* arg0 in card_dev_menu_wait_countdown; pointer addresses record offset 0x10 */

/* Decrement the record's countdown and switch its pointer when the count goes negative. */
void card_dev_menu_wait_countdown(void *record_data) {
    s32 countdown;

    countdown = ((S_8001EEAC_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_8001EEAC_0 *)((u8 *)record_data - 0x10))->unk_4C = countdown;
    if (countdown < 0) {
        ((S_8001EEAC_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80405DE0;
    }
}

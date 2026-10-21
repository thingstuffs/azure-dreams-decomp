#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "main/data.h"

typedef struct S_80026398_0 {
    s32 * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_80026398_0;   /* arg0 in card_boot_wait_before_saving_slot; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */

/* Decrement the record's countdown and reset its pointer when it becomes negative. */
void card_boot_wait_before_saving_slot(void *record_data) {
    s32 countdown;

    countdown = ((S_80026398_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_80026398_0 *)((u8 *)record_data - 0x10))->unk_4C = countdown;
    if (countdown < 0) {
        ((S_80026398_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800262BC;
    }
}

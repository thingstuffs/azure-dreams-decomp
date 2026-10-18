#include "common.h"

typedef struct S_800252A4_0 {
    s32 * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_800252A4_0;   /* arg0 in card_boot_wait_before_loading_slot; pointer addresses record offset 0x10 */
void card_boot_load_selected_slot(s8 *state);

/* Decrement the record's countdown and set its pointer when the countdown becomes negative. */
void card_boot_wait_before_loading_slot(void *record_data) {
    s32 countdown;

    countdown = ((S_800252A4_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_800252A4_0 *)((u8 *)record_data - 0x10))->unk_4C = countdown;
    if (countdown < 0) {
        ((S_800252A4_0 *)((u8 *)record_data - 0x10))->unk_00 = &card_boot_load_selected_slot;
    }
}

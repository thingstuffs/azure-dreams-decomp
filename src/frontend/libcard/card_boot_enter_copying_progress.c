#include "common.h"

typedef struct S_80025494_0 {
    s32 * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
    s32 unk_50;
} S_80025494_0;   /* arg0 in card_boot_enter_copying_progress; pointer addresses record offset 0x10 */


#include "frontend/libcard/interfaces.h"

/* Sets two state fields, initializes embedded data, and assigns the record pointer. */
void card_boot_enter_copying_progress(void *object_data) {
    ((S_80025494_0 *)((u8 *)object_data - 0x10))->unk_4C = 1;
    card_boot_show_copying_progress(object_data - 0x20, object_data + 0x40);
    ((S_80025494_0 *)((u8 *)object_data - 0x10))->unk_50 = 1;
    ((S_80025494_0 *)((u8 *)object_data - 0x10))->unk_00 = &card_boot_wait_before_copying_slot;
}

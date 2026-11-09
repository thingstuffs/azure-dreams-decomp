#include "frontend/libcard/slot_list.h"
#include "common.h"
#include "frontend/libcard.h"

/* Clear the ten values referenced by the pointer table at offset 0x25C. */
void card_boot_clear_ten_display_slots(CardSlotWindow *object) {
    s32 slot;
    for (slot = 0; slot < 10; slot++) {
        object->pointers[slot]->unk_00 = 0;
    }
}

#include "common.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

extern void inventory_set_object_entry_address(void *);


/* Selects write_text_and_advance_selection when the state field is nonzero or calls inventory_set_object_entry_address. */
void card_boot_handle_overwrite_answer(void *object_data) {
    if (*(s32 *)((u8 *)object_data + 0x38) != 0) {
        *(s32 **)((u8 *)object_data - 0x10) = write_text_and_advance_selection;
        return;
    }
    inventory_set_object_entry_address(object_data);
}

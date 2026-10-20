#include "common.h"
#include "frontend/libcard/interfaces.h"

extern void inventory_set_object_entry_address(void *);
extern s32 D_800265B8[];

/* Selects D_800265B8 when the state field is nonzero or calls inventory_set_object_entry_address. */
void card_boot_handle_overwrite_answer(void *object_data) {
    if (*(s32 *)((u8 *)object_data + 0x38) != 0) {
        *(s32 **)((u8 *)object_data - 0x10) = &D_800265B8[0];
        return;
    }
    inventory_set_object_entry_address(object_data);
}

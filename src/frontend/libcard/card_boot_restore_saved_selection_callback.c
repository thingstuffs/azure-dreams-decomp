#include "frontend/libcard_callbacks_api.h"
#include "common.h"
#include "frontend/libcard/save_menu.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"

/* Clears flag 0x2000 and restores the saved record value when set. */
void card_boot_restore_saved_selection_callback(void *object_data) {
    u16 flags;
    ObjectNodeHeader *object_header;

    object_header = (ObjectNodeHeader *)object_data - 1;
    flags = object_header->flags;
    if (flags & 0x2000) {
        CardMenuCallbackPrefix *state = object_data;

        object_header->flags = (u16)(flags & 0xDFFF);
        *(void **)((u8 *)object_data - 0x10) = state->saved_callback;
    }
}

#include "common.h"
#include "frontend/card.h"

#include "frontend/card/server_aliases.h"

/* Set bit 0x8000 in the object and global flags when the object exists. */
void card_dev_flag_object_dirty(void *object) {
    if (object != 0) {
        u16 *flags_ptr = (u16 *)((u8 *)object + 0x1E);
        u16 object_flags = *flags_ptr;
        s32 global_flags = card_ui_dirty_flags;
        object_flags |= 0x8000;
        global_flags |= 0x8000;
        *flags_ptr = object_flags;
        card_ui_dirty_flags = global_flags;
    }
}

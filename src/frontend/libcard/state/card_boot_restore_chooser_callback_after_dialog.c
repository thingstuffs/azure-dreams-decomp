#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/libcard/state.h"

/* Clear flag 0x2000 and restore the saved field when the flag is set. */
void card_boot_restore_chooser_callback_after_dialog(void *record_part) {
    u16 flags;
    ObjectNodeHeader *base_record;

    base_record = record_part - 0x20;
    flags = base_record->flags;
    if (flags & 0x2000) {
        base_record->flags = (u16) (flags & 0xDFFF);
        ((CardChooserBody *)((u8 *)record_part - 0x10))->mode = (s32) ((CardChooserBody *)((u8 *)record_part
            - 0x10))->unk_3C;
    }
}

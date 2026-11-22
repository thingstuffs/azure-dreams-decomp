#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/libcard/state.h"

/* Restore the chooser callback when its notice completes. */
void card_boot_restore_chooser_mode(CardChooserBody *menu) {
    u16 flags;
    ObjectNodeHeader *base_record;

    base_record = NODE_HEADER(menu);
    flags = base_record->flags;
    if (flags & 0x2000) {
        base_record->flags = (u16) (flags & 0xDFFF);
        NODE_HEADER(menu)->update_callback = menu->resume_input;
    }
}

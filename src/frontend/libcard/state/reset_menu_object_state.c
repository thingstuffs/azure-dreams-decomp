#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/libcard/state.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* Clear flag 0x2000 and restore the saved field when the flag is set. */
void reset_menu_object_state_2(void *record_part) {
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

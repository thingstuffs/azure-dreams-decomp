#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

/* extern */

typedef struct GapPlayerSlot {
    u8 pad_00[0x40];
    s32 unk_40;
} GapPlayerSlot;   /* arg0 in clear_indexed_entry_and_initialize_handler_table */


void initialize_target_and_handler_table(GapPlayerSlot *, s32);
/* Clear the indexed table entry and call initialize_target_and_handler_table. */
void clear_indexed_entry_and_initialize_handler_table(GapPlayerSlot *object, s32 value) {
    D_80082660[object->unk_40].unk_00 = 0;
    initialize_target_and_handler_table(object, value);
}

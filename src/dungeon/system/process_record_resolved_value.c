#include "common.h"
#include "m2c_compat.h"
#include "dungeon/item.h"
#include "dungeon/menu.h"

s32 get_work_value();                             /* extern */

typedef struct S_800257C0_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800257C0_0;   /* arg0 in process_record_resolved_value */

/* Processes the record header and its resolved value, then returns success. */
s32 process_record_resolved_value(void *record_arg) {
    S_800257C0_0 *record = record_arg;

    inventory_clear_object_field_and_entry(record_arg - 0x20);
    initialize_menu_object_state(get_work_value(record->unk_14), record->unk_08);
    return 1;
}

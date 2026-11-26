#include "common.h"
#include "town/scene.h"

/* TOWN bank at link delta 0x7FA17000: the reference module is the one that defines sell_flagged_entries.
 * The callee is this bank's mirror of sell_flagged_entries (src/town/system/shop_value_dispatch.c),
 * which takes a pointer to a four-byte-entry list.  Evidence: docs/evidence/r121_rem_opus.md. */

extern u8 D_800188D0[];

/* Calls func_80017108 with D_800188D0. */
void process_entry_list_in_mode_one(void) {
    process_flagged_entries_after_header(D_800188D0);
}

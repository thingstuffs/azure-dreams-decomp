#include "common.h"
#include "town/scene.h"

/* TOWN bank at link delta 0x7FC16000: see src/town/func_804811DC.c for the module identity.
 * The callee is this bank's mirror of sell_flagged_entries (src/town/func_8032EB08.c),
 * which takes a pointer to a four-byte-entry list.  Evidence: docs/evidence/r121_rem_opus.md. */

extern u8 D_80019440[];

/* Calls process_flagged_entries_after_header with D_80019440. */
void process_entry_list_mode_1(void) {
    process_flagged_entries_after_header(D_80019440);
}

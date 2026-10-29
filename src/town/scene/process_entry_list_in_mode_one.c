#include "common.h"
#include "town/scene.h"

/* TOWN bank at link delta 0x7FA17000: see src/town/func_80680108.c for the module identity.
 * The callee is this bank's mirror of process_lshop_value_plus_four (src/town/func_8032EB08.c),
 * which takes a pointer to a four-byte-entry list.  Evidence: docs/evidence/r121_rem_opus.md. */

extern u8 D_800188D0[];
extern void func_80017108(u8 *entries);

/* Calls func_80017108 with D_800188D0. */
void process_entry_list_in_mode_one(void) {
    func_80017108(D_800188D0);
}

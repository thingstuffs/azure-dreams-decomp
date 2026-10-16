#include "common.h"

/* TOWN bank at link delta 0x7FA17000: see src/town/func_80680108.c for the module identity.
 * The callee is this bank's mirror of townProcessLshopValuePlusFour (src/town/func_8032EB08.c),
 * which takes a pointer to a four-byte-entry list.  Evidence: docs/evidence/r121_rem_opus.md. */

extern u8 D_800188D0[];
extern void func_80017108(u8 *entries);

/* Process the entry list D_800188D0 in mode 1. */
void func_80016850(void) {
    func_80017108(D_800188D0);
}

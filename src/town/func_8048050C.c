#include "common.h"

/* TOWN bank at link delta 0x7FC16000: see src/town/func_804811DC.c for the module identity.
 * The callee is this bank's mirror of townProcessLshopValuePlusFour (src/town/func_8032EB08.c),
 * which takes a pointer to a four-byte-entry list.  Evidence: docs/evidence/r121_rem_opus.md. */

extern u8 D_80019440[];
extern void func_800171DC(u8 *entries);

/* Process the entry list D_80019440 in mode 1. */
void func_8001650C(void) {
    func_800171DC(D_80019440);
}

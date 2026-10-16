#include "common.h"

/* TOWN bank at file 0x595730..0x5970E8 (link delta 0x7FA81800) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AFD1C (delta 0x7FD6A800): the 6584 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors townProcessLshopValue
 * (src/town/func_8032EAE8.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = townProcessLshopEntries of the reference module (src/town/func_8032EA2C.c). */
extern void func_800175F8(void *entries, s32 entry_mode);

/* Process the flagged entries in mode 0 (append them to the object list). */
void func_800176B4(void *entries) {
    func_800175F8(entries, 0);
}

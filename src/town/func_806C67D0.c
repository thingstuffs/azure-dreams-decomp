#include "common.h"

/* TOWN bank at file 0x64603C..0x647A04 (link delta 0x7F9D1000) is a copy of
 * the matched module at TOWN file 0x2AE354..0x2AFD1C (delta 0x7FD6A800): the 6600 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors townProcessLshopValue
 * (src/town/func_8032EAE8.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = townProcessLshopEntries of the reference module (src/town/func_8032EA2C.c). */
extern void func_80017714(void *entries, s32 entry_mode);

/* Process the flagged entries in mode 0 (append them to the object list). */
void func_800177D0(void *entries) {
    func_80017714(entries, 0);
}

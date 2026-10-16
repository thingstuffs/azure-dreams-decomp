#include "common.h"

/* TOWN bank at file 0x581360..0x582D18 (link delta 0x7FA95000) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AFD1C (delta 0x7FD6A800): the 6584 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors func_800192E8
 * (src/town/func_8032EAE8.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = func_8001922C of the reference module (src/town/func_8032EA2C.c). */
extern void func_80016A28(void *entries, s32 entry_mode);

/* Process the flagged entries in mode 0 (append them to the object list). */
void func_80016AE4(void *entries) {
    func_80016A28(entries, 0);
}

#include "common.h"

/* TOWN bank at file 0x5FF964..0x6001F4 (link delta 0x7FA17000) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AEBF4 (delta 0x7FD6A800): the 2192 bytes
 * are identical except relocated fields, and 11 of 12 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors townProcessLshopValuePlusFour
 * (src/town/func_8032EB08.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = townProcessLshopEntries of the reference module (src/town/func_8032EA2C.c). */
extern void townSetSceneLinkedRecordOffsets(void *entries, s32 entry_mode);

/* Process the flagged entries that follow the four-byte header, in mode 1. */
void func_80017108(u8 *entries) {
    townSetSceneLinkedRecordOffsets(entries + 4, 1);
}

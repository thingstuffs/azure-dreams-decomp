#include "common.h"

/* TOWN bank at file 0x5FF964..0x6001F4 (link delta 0x7FA17000) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AEBF4 (delta 0x7FD6A800): the 2192 bytes
 * are identical except relocated fields, and 11 of 12 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors townProcessLshopValue
 * (src/town/func_8032EAE8.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = townProcessLshopEntries of the reference module (src/town/func_8032EA2C.c). */
extern void townSetSceneLinkedRecordOffsets(void *entries, s32 entry_mode);

/* Process the flagged entries in mode 0 (append them to the object list). */
void func_800170E8(void *entries) {
    townSetSceneLinkedRecordOffsets(entries, 0);
}

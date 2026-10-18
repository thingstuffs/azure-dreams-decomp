#include "common.h"

/* TOWN bank at file 0x51EB34..0x5205FC (link delta 0x7FAF8000) is a copy of
 * the matched module at TOWN file 0x2AE254..0x2AFD1C (delta 0x7FD6A800): the 6856 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors process_lshop_value
 * (src/town/func_8032EAE8.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = process_lshop_entries of the reference module (src/town/func_8032EA2C.c). */
extern void func_8001730C(void *entries, s32 entry_mode);

/* Process the flagged entries in mode 0 (append them to the object list). */
void append_flagged_entries_to_object_list(void *entries) {
    func_8001730C(entries, 0);
}

#include "common.h"

/* TOWN bank at file 0x595730..0x5970E8 (link delta 0x7FA81800) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AFD1C (delta 0x7FD6A800): the 6584 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors process_lshop_value_plus_four
 * (src/town/func_8032EB08.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = process_lshop_entries of the reference module (src/town/func_8032EA2C.c). */
extern void func_800175F8(void *entries, s32 entry_mode);

/* Process the flagged entries that follow the four-byte header, in mode 1. */
void select_next_eligible_wrapped_entry(u8 *entries) {
    func_800175F8(entries + 4, 1);
}

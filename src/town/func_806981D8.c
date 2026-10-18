#include "common.h"

/* TOWN bank at file 0x617A34..0x6182C4 (link delta 0x7F9FF000) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AEBF4 (delta 0x7FD6A800): the 2192 bytes
 * are identical except relocated fields, and 11 of 12 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors process_lshop_value_plus_four
 * (src/town/func_8032EB08.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = process_lshop_entries of the reference module (src/town/func_8032EA2C.c). */
extern void func_800170FC(void *entries, s32 entry_mode);

/* Process the flagged entries that follow the four-byte header, in mode 1. */
void func_800171D8(u8 *entries) {
    func_800170FC(entries + 4, 1);
}

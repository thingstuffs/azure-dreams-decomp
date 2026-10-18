#include "common.h"

/* TOWN bank at file 0x64603C..0x647A04 (link delta 0x7F9D1000) is a copy of
 * the matched module at TOWN file 0x2AE354..0x2AFD1C (delta 0x7FD6A800): the 6600 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors process_lshop_value_plus_four
 * (src/town/func_8032EB08.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = process_lshop_entries of the reference module (src/town/func_8032EA2C.c). */
extern void func_80017714(void *entries, s32 entry_mode);

/* Process the flagged entries that follow the four-byte header, in mode 1. */
void func_800177F0(u8 *entries) {
    func_80017714(entries + 4, 1);
}

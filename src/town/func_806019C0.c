#include "common.h"

/* TOWN bank at file 0x581360..0x582D18 (link delta 0x7FA95000) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AFD1C (delta 0x7FD6A800): the 6584 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors refresh_lshop_entry_list
 * (src/town/func_8032E9C4.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = release_lshop_entry / compact_lshop_entry_list of the reference module (src/town/func_8032E634.c,
 * src/town/func_8032E6A8.c): clear one object slot, then compact the slot list. */
extern void process_ids_conditionally_pointer(s32 slotIndex);
extern void pass_2(void);

/* Release the object in the given slot and compact the slot list. */
void func_800169C0(s32 slotIndex) {
    process_ids_conditionally_pointer(slotIndex);
    pass_2();
}

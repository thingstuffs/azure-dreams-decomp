#include "common.h"

/* TOWN bank at file 0x617A34..0x6182C4 (link delta 0x7F9FF000) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AEBF4 (delta 0x7FD6A800): the 2192 bytes
 * are identical except relocated fields, and 11 of 12 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors refresh_lshop_entry_list
 * (src/town/func_8032E9C4.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = release_lshop_entry / compact_lshop_entry_list of the reference module (src/town/func_8032E634.c,
 * src/town/func_8032E6A8.c): clear one object slot, then compact the slot list. */
extern void func_80016D04(s32 slotIndex);
extern void select_data_array_based_flag(void);

/* Release the object in the given slot and compact the slot list. */
void func_80017094(s32 slotIndex) {
    func_80016D04(slotIndex);
    select_data_array_based_flag();
}

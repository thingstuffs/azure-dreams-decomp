#include "common.h"

/* TOWN bank at file 0x5FF964..0x6001F4 (link delta 0x7FA17000) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AEBF4 (delta 0x7FD6A800): the 2192 bytes
 * are identical except relocated fields, and 11 of 12 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors refresh_lshop_entry_list
 * (src/town/func_8032E9C4.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = release_lshop_entry / compact_lshop_entry_list of the reference module (src/town/func_8032E634.c,
 * src/town/func_8032E6A8.c): clear one object slot, then compact the slot list. */
extern void init_object_set_runtime_pointers_rev_b(s32 slotIndex);
extern void func_80016CA8(void);

/* Release the object in the given slot and compact the slot list. */
void process_current_town_cell(s32 slotIndex) {
    init_object_set_runtime_pointers_rev_b(slotIndex);
    func_80016CA8();
}

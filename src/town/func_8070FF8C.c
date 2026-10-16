#include "common.h"

/* TOWN bank at file 0x68F91C..0x6912E4 (link delta 0x7F989000) is a copy of
 * the matched module at TOWN file 0x2AE354..0x2AFD1C (delta 0x7FD6A800): the 6600 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors townRefreshLshopEntryList
 * (src/town/func_8032E9C4.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = townReleaseLshopEntry / townCompactLshopEntryList of the reference module (src/town/func_8032E634.c,
 * src/town/func_8032E6A8.c): clear one object slot, then compact the slot list. */
extern void func_80018BFC(s32 slotIndex);
extern void func_80018C70(void);

/* Release the object in the given slot and compact the slot list. */
void func_80018F8C(s32 slotIndex) {
    func_80018BFC(slotIndex);
    func_80018C70();
}

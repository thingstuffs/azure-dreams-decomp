#include "common.h"

/* TOWN bank at file 0x51EB34..0x5205FC (link delta 0x7FAF8000) is a copy of
 * the matched module at TOWN file 0x2AE254..0x2AFD1C (delta 0x7FD6A800): the 6856 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors func_800191C4
 * (src/town/func_8032E9C4.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = func_80018E34 / func_80018EA8 of the reference module (src/town/func_8032E634.c,
 * src/town/func_8032E6A8.c): clear one object slot, then compact the slot list. */
extern void func_80016F14(s32 slotIndex);
extern void func_80016F88(void);

/* Release the object in the given slot and compact the slot list. */
void func_800172A4(s32 slotIndex) {
    func_80016F14(slotIndex);
    func_80016F88();
}

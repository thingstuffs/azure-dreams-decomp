#include "common.h"

/* TOWN bank at file 0x595730..0x5970E8 (link delta 0x7FA81800) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AFD1C (delta 0x7FD6A800): the 6584 bytes
 * are identical except relocated fields, and 21 of 21 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors func_800191C4
 * (src/town/func_8032E9C4.c).  Evidence: docs/evidence/r121_rem_opus.md. */

/* = func_80018E34 / func_80018EA8 of the reference module (src/town/func_8032E634.c,
 * src/town/func_8032E6A8.c): clear one object slot, then compact the slot list. */
extern void func_80017200(s32 slotIndex);
extern void func_80017274(void);

/* Release the object in the given slot and compact the slot list. */
void func_80017590(s32 slotIndex) {
    func_80017200(slotIndex);
    func_80017274();
}

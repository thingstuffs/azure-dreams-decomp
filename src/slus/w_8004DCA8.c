#include "common.h"

/* D_80083D98: 32-slot table of registered pointers (0x80 bytes to the next
   symbol D_80083E18, /4 = 32 void* entries).
   D_80081554: gp-rel "next free slot" counter, reset alongside D_80081558 in
   func_8004DDB4 (D_80081554 = 0;).
   D_80080B68: fallback/default object whose ADDRESS is registered when the
   caller passes NULL; only its address is used here (never dereferenced), so
   it is declared oversized (>8 bytes) purely to force %hi/%lo codegen for a
   direct (non gp-rel) global per this codebase's addressing convention. */
extern void *D_80083D98[32];
extern int D_80081554;
extern int D_80080B68[3];

/* Registers a0 (or, if a0 is NULL, the address of the fallback object
   D_80080B68) into the next free slot of D_80083D98, then advances the
   slot counter D_80081554. */
void func_8004DCA8(void *a0)
{
    /* Pinned to $5/a1 to match retail's register allocation for this
       symbol-address computation: gcc 2.8's default allocator routes the
       %hi/%lo pair for D_80080B68's address through a scratch temp (colliding
       with the D_80083D98 base held in v0 and forcing a redundant re-lui),
       whereas retail computes it directly into the destination register. */
    register void *a1 ASM_REG("$5") = a0;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (a1 == 0) {
        a1 = D_80080B68;
    }
    D_80083D98[D_80081554++] = a1;
}

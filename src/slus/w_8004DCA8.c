#include "slus/command_slots_81554.h"

/* D_80083D98: 32-slot table of command words and addresses (0x80 bytes to
   the next symbol D_80083E18, /4 = 32 word entries).
   D_80081554: gp-rel "next free slot" counter, reset alongside D_80081558 in
   func_8004DDB4 (D_80081554 = 0;).
   D_80080B68: fallback return-script byte whose ADDRESS is registered when
   the caller passes NULL. The audited opcode 0x16 pops/restores the caller
   cursor; this one-byte used view does not assert historical allocation. */
extern u8 D_80080B68[1];

/* Registers the object or its fallback in the next slot and advances the slot counter. */
void func_8004DCA8(void *object)
{
    void *registered_ptr = object;
    if (registered_ptr == 0) {
        registered_ptr = D_80080B68;
    }
    D_80083D98[D_80081554++] = (s32)registered_ptr;
}

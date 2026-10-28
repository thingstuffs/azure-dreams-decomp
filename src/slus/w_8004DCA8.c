#include "slus/command_slots_81554.h"
#include "slus.h"

/* D_80083D98: 32-slot table of command words and addresses (0x80 bytes to
   the next symbol D_80083E18, /4 = 32 word entries).
   D_80081554: gp-rel "next free slot" counter, reset alongside D_80081558 in
   func_8004DDB4 (D_80081554 = 0;).
   D_80080B68: fallback return-script byte whose ADDRESS is registered when
   the caller passes NULL. The audited opcode 0x16 pops/restores the caller
   cursor; this one-byte used view does not assert historical allocation. */
extern u8 script_message_default_record[1];

/* Registers the object or its fallback in the next slot and advances the slot counter. */
void runtime_register_object_or_fallback_slot(void *object)
{
    void *registered_ptr = object;
    if (registered_ptr == 0) {
        registered_ptr = script_message_default_record;
    }
    script_message_command_words[message_command_write_index++] = (s32)registered_ptr;
}

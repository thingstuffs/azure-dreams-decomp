#include "common.h"
#include "m2c_compat.h"

s16 release_entity_slot_and_update_flags();          /* extern */
extern M2C_UNK D_80010248;

typedef struct S_800F6514_0 {
    u8 unk_00;
    u8 unk_01;
} S_800F6514_0;

/* Process entries whose first two bytes are 2 and 0x13 in the 20-entry table. */
void apply_special_item_slot_action(void) {
    s32 *entry;
    s32 entry_index;

    entry = (s32 *) 0x80010248;
    entry_index = 0;
    do {
        if ((((S_800F6514_0 *)entry)->unk_01 == 0x13) && (((S_800F6514_0 *)entry)->unk_00 == 2)) {
            release_entity_slot_and_update_flags(entry, 1);
        }
        entry_index += 1;
        entry += 1;
    } while (entry_index < 0x14);
}

/* MECHANISM: A fixed-address pointer literal forces retail's lui/ori base construction.
   Advancing one s32 element gives the four-byte loop stride while preserving
   the seed's 0x28 frame, saved-register hold set, and delay-slot CFG. */

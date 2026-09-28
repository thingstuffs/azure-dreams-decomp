#include "common.h"
#include "shared/def_table.h"

typedef struct {
    u8 pad0[0x11];
    u8 kind;
    u8 pad12[2];
} DungeonEntry;


/* Return the first of three slots with a matching entry kind, or -1. */
s16 func_800A3544(u8 *slots, u8 kind) {
    s32 slot_index;

    for (slot_index = 0; slot_index < 3; slot_index++) {
        if (slots[slot_index * 3 + 8] != 0 && D_8006DE24[slots[slot_index * 3 + 8]].unk_11 == kind) {
            return slot_index;
        }
    }
    return -1;
}

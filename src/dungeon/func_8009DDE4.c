#include "common.h"

typedef struct {
    u8 pad0[0x11];
    u8 kind;
    u8 pad12[2];
} DungeonEntry;

extern DungeonEntry D_8006DE24[];

/* Return the first of three slots with a matching entry kind, or -1. */
s16 func_800A3544(u8 *slots, u8 kind) {
    s32 slot_index = 0;
    DungeonEntry *entries = D_8006DE24;

    for (; slot_index < 3; slot_index++, slots += 3) {
        u8 entry_index = slots[8];

        if (entry_index != 0) {
            u32 entry_offset = entry_index * sizeof(DungeonEntry);
            register DungeonEntry *entry ASM_REG("$3") =
                (DungeonEntry *)(entry_offset + (u32)entries);

            if (entry->kind == kind) {
                return slot_index;
            }
        }
    }
    return -1;
}

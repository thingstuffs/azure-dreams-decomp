#include "common.h"
#include "shared/dungeon_status.h"

extern s32 generate_random_value(void);

/* Stores the low four bits of the computed result in the global slot. */
void store_random_nibble(void) {
    g_dungeon_status.unk_06 = generate_random_value() & 0xF;
}

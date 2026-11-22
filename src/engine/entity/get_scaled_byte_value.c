#include "shared/dungeon_item_entries.h"

/* Returns the signed byte scaled by ten times the mask, or unchanged if the mask is zero. */
int get_scaled_byte_value(DungeonItemEntry *item) {
    int mask = item->unk_03 & 0x1F;
    int value = item->unk_02;

    if (mask != 0) {
        value = value * (10 * mask);
    }
    return value;
}

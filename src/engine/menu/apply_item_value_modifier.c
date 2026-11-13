#include "common.h"
#include "engine/menu.h"
#include "shared/dungeon_item_entries.h"

/* Applies a signed correction and optional fivefold multiplier to the base value, with a minimum of one. */
s32 apply_item_value_modifier(s32 base_value, DungeonItemEntry *modifier) {
    s32 result = base_value + ((u32)base_value / 10) * modifier->unk_02;

    if (modifier->unk_03 & 0x40) {
        result = result * 5;
    }

    if (result <= 0) {
        result = 1;
    }

    return result;
}

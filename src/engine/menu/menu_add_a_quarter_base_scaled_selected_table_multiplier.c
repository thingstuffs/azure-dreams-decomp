#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "engine/menu.h"

/* struct occupying an 84-byte (0x54) slot in the fixed-address table at 0x800102F0;
   only offset 0x11 accessed here. The retail asm materialises the table base via
   lui+ORI (not lui+addiu/%hi/%lo(symbol)) -> the original source referenced this
   table through a raw compile-time literal address cast, not a linked extern symbol. */
typedef struct {
    u8 pad0[0x11];
    u8 field_11;
    u8 pad1[0x54 - 0x12];
} S_8004A534_Entry;

#define TBL_800102F0 ((S_8004A534_Entry *)0x800102F0)

/*
 * Adds the unsigned base shifted right two bits times the field_11 multiplier selected by the low
 * five bits of field_3.
 */
s32 menu_add_a_quarter_base_scaled_selected_table_multiplier(u32 base_value, DungeonItemEntry *entry_selector) {
    return base_value + ((base_value >> 2) * TBL_800102F0[entry_selector->unk_03 & 0x1F].field_11);
}

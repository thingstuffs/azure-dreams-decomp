#include "common.h"

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

/* caller struct: only byte offset 3 (a bitfield/index, masked to 0x1F) accessed here */
typedef struct {
    u8 pad0[3];
    u8 field_3;
} S_8004A534_arg1;

/* Adds a quarter of the base value scaled by the selected table multiplier. */
s32 func_8004A534(u32 base_value, S_8004A534_arg1 *entry_selector) {
    return base_value + ((base_value >> 2) * TBL_800102F0[entry_selector->field_3 & 0x1F].field_11);
}

#include "common.h"
#include "town/menu.h"

extern u8 D_80127A40[];

/* Return the low bit of the packed two-bit flag selected by the lookup table. */
u8 is_catalog_entry_available(s32 index) {
    u8 flag_index;

    index &= 0xFF;
    flag_index = D_80127A40[index];
    return (((u8 *)0x80013614)[flag_index >> 2] >> ((flag_index & 3) * 2)) & 1;
}

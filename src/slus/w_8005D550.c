#include "slus/sound_register_helpers.h"

/* Store a table entry, optionally shifting the value right by the global shift amount. */
void store_u16_table_entry(s32 index, u32 value, s32 apply_shift)
{
    if (apply_shift == 0) {
        ((SoundRegister16 *)D_80079958)[index] = (u16)value;
    } else {
        ((SoundRegister16 *)D_80079958)[index] = (u16)(value >> D_80079980);
    }
}

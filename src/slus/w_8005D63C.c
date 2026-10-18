#include "slus/sound_register_helpers.h"

/* Read a table value and apply the global left shift unless shift mode is -1. */
s32 load_u16_table_entry_scaled(s32 index, s32 shift_mode)
{
    u16 value = D_80079958[index];

    if (shift_mode == -1) {
        return (s32)value;
    }
    return (s32)value << D_80079980;
}

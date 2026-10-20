#include "engine/audio/spu/sound_register_helpers.h"

#include "engine/audio/spu/sound_register_helpers.h"

/* Store a table entry, optionally shifting the value right by the global shift amount. */
void store_u16_table_entry(s32 index, u32 value, s32 apply_shift)
{
    if (apply_shift == 0) {
        ((SoundRegister16 *)D_80079958)[index] = (u16)value;
    } else {
        ((SoundRegister16 *)D_80079958)[index] = (u16)(value >> D_80079980);
    }
}
#include "engine/audio/spu/sound_register_helpers.h"

/* Read a table value and apply the global left shift unless shift mode is -1. */
s32 load_u16_table_entry_scaled(s32 index, s32 shift_mode)
{
    u16 value = D_80079958[index];

    if (shift_mode == -1) {
        return (s32)value;
    }
    return (s32)value << D_80079980;
}
#include "engine/audio/spu/sound_register_helpers.h"

/* Replaces status bits 0x70000 with 0x30000 when use_status_3 is nonzero, otherwise 0x50000. */
void set_driver_status_bits(s32 use_status_3) {
    *D_80079968 &= ~0x70000;
    if (use_status_3) {
        *D_80079968 |= 0x30000;
    } else {
        *D_80079968 |= 0x50000;
    }
}

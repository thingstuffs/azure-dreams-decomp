#include "engine/audio/spu/sound_register_helpers.h"

#include "engine/audio/spu/sound_register_helpers.h"
#include "engine/audio/spu.h"

/* Optionally aligns a value, shifts it, and stores or returns the result. */
s32 audio_handle_optionally_aligns_shifts_stores_returns_result(s32 index, u32 value)
{
    s32 store_index = index;
    u32 shifted_value;

    if (spu_address_alignment_enabled != 0) {
        s32 alignment = spu_address_alignment;
        if (value % alignment != 0) {
            value = value + alignment;
            value = value & ~spu_address_alignment_mask;
        }
    }

    shifted_value = value >> spu_address_unit_shift;

    switch (store_index) {
    case -1:
        return (u16)shifted_value;
    case -2:
        return value;
    default:
        spu_registers[store_index] = (u16)shifted_value;
        return value;
    }
}

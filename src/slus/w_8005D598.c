#include "slus/sound_register_helpers.h"

/* Optionally aligns a value, shifts it, and stores or returns the result. */
s32 func_8005D598(s32 index, u32 value)
{
    s32 store_index = index;
    u32 shifted_value;

    if (D_8007997C != 0) {
        s32 alignment = D_80079984;
        if (value % alignment != 0) {
            value = value + alignment;
            value = value & ~D_80079988;
        }
    }

    shifted_value = value >> D_80079980;

    switch (store_index) {
    case -1:
        return (u16)shifted_value;
    case -2:
        return value;
    default:
        D_80079958[store_index] = (u16)shifted_value;
        return value;
    }
}

#include "slus/sound_transfer_helpers.h"

/* Latches and shifts the value for an in-range address, or returns zero. */
s32 func_8005ECA0(s32 address)
{
    u16 shift_input;

    if ((u32)(address - 0x1010) > 0x7EFE8) {
        return 0;
    }

    shift_input = (u16)func_8005D598(-1, address);
    D_80079970 = shift_input;
    return (s32)shift_input << D_80079980;
}

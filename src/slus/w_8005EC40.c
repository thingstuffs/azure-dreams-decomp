#include "slus/sound_transfer_helpers.h"

/* Applies and returns the rate capped at 0x7EFF0, clearing the flag when the queue is inactive. */
s32 clampAndSubmitDriverParameter(s32 voice, u32 rate)
{
    u32 clamped_rate = rate;

    if (clamped_rate > 0x7EFF0) {
        clamped_rate = 0x7EFF0;
    }

    submitDriverTransferWithFallback(voice, clamped_rate);

    if (D_80079990 == 0) {
        D_8007998C = 0;
    }

    return clamped_rate;
}

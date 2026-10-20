#include "engine/audio/spu/sound_transfer_helpers.h"



/* Applies and returns the rate capped at 0x7EFF0, clearing the flag when the queue is inactive. */
s32 clamp_and_submit_driver_parameter(s32 voice, u32 rate)
{
    u32 clamped_rate = rate;

    if (clamped_rate > 0x7EFF0) {
        clamped_rate = 0x7EFF0;
    }

    submit_driver_transfer_with_fallback(voice, clamped_rate);

    if (spu_transfer_callback == 0) {
        spu_transfer_complete = 0;
    }

    return clamped_rate;
}

/* Latches and shifts the value for an in-range address, or returns zero. */
s32 lookup_and_scale_driver_address(s32 address)
{
    u16 shift_input;

    if ((u32)(address - 0x1010) > 0x7EFE8) {
        return 0;
    }

    shift_input = (u16)audio_handle_optionally_aligns_shifts_stores_returns_result(-1, address);
    spu_transfer_address_units = shift_input;
    return (s32)shift_input << spu_address_unit_shift;
}

/* Polls or waits for SPU transfer completion and latches the completion status. */
s32 poll_driver_completion_event(s32 wait_for_completion)
{
    s32 event_status;

    if (spu_transfer_completion_override == 1 || spu_transfer_complete == 1) {
        return 1;
    }

    event_status = TestEvent(spu_transfer_event_handle);
    if (wait_for_completion == 1) {
        if (event_status == 0) {
            while (TestEvent(spu_transfer_event_handle) == 0) {
            }
        }
        event_status = 1;
    } else {
        if (event_status != 1) {
            return event_status;
        }
    }

    spu_transfer_complete = event_status;
    return event_status;
}

/* SPU transfer size and address limits, plus completion-event polling. */
#include "engine/audio/spu/sound_transfer_helpers.h"
#include "engine/audio/spu.h"



/* Write data to sound RAM at the current transfer address, capping the size at 0x7EFF0 and returning it. */
s32 write_spu_transfer_data(s32 data, u32 size)
{
    u32 clamped_size = size;

    if (clamped_size > 0x7EFF0) {
        clamped_size = 0x7EFF0;
    }

    _spu_Fw(data, clamped_size);

    if (spu_transfer_callback == 0) {
        spu_transfer_complete = 0;
    }

    return clamped_size;
}

/* Latches and shifts the value for an in-range address, or returns zero. */
s32 SpuSetTransferStartAddr(s32 address)
{
    u16 shift_input;

    if ((u32)(address - 0x1010) > 0x7EFE8) {
        return 0;
    }

    shift_input = (u16)_spu_FsetRXXa(-1, address);
    spu_transfer_address_units = shift_input;
    return (s32)shift_input << spu_address_unit_shift;
}

/* Polls or waits for SPU transfer completion and latches the completion status. */
s32 SpuIsTransferCompleted(s32 wait_for_completion)
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

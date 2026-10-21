#include "slus/sound_streaming_transfer.h"
#include "slus.h"


/* Streams sample data to a voice in SPU chunks, preserving busy and pending queue state. */
s32 clear_spu_reverb_work_area(s32 voice)
{
    s32 voice_or_chunk_size = voice;
    s32 remaining, spu_addr, more_chunks, saved_busy, restore_busy = 0;
    volatile s32 pending_swap = 0;

    if ((u32)voice_or_chunk_size >= 10)
        return -1;

    if (test_spu_blocks_beyond_address(spu_reverb_start_addresses[voice_or_chunk_size]) != 0)
        return -1;

    if (voice_or_chunk_size == 0) {
        remaining = 0x10 << spu_address_unit_shift;
        spu_addr = 0xFFF0 << spu_address_unit_shift;
    } else {
        remaining = (0x10000 - spu_reverb_start_addresses[voice_or_chunk_size]) << spu_address_unit_shift;
        spu_addr = spu_reverb_start_addresses[voice_or_chunk_size] << spu_address_unit_shift;
    }

    saved_busy = spu_transfer_uses_fifo;
    if (saved_busy == 1) {
        spu_transfer_address_units[1] = 0;
        restore_busy = 1;
    }

    more_chunks = 1;
    if (spu_transfer_callback[0] != 0) {
        pending_swap = spu_address_alignment_mask[2];
        spu_transfer_complete[1] = 0;
    }

    do {
        if ((u32)remaining >= 0x401) {
            voice_or_chunk_size = 0x400;
        } else {
            voice_or_chunk_size = remaining;
            more_chunks = 0;
        }

        dispatch_spu_dma_transfer_command(2, spu_addr);
        dispatch_spu_dma_transfer_command(1);
        dispatch_spu_dma_transfer_command(3, spu_reverb_clear_buffer, voice_or_chunk_size);
        WaitEvent(spu_transfer_event_handle);
        remaining -= 0x400;
        spu_addr += 0x400;
    } while (more_chunks);

    if (restore_busy)
        spu_transfer_address_units[1] = saved_busy;

    if (pending_swap != 0)
        spu_transfer_callback[0] = pending_swap;

    return 0;
}

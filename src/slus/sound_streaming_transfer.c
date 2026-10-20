#include "slus/sound_streaming_transfer.h"


/* Streams sample data to a voice in SPU chunks, preserving busy and pending queue state. */
s32 func_8005E7E0(s32 voice)
{
    s32 voice_or_chunk_size = voice;
    s32 remaining, spu_addr, more_chunks, saved_busy, restore_busy = 0;
    volatile s32 pending_swap = 0;

    if ((u32)voice_or_chunk_size >= 10)
        return -1;

    if (func_8005D9DC(D_800799C0[voice_or_chunk_size]) != 0)
        return -1;

    if (voice_or_chunk_size == 0) {
        remaining = 0x10 << D_80079980;
        spu_addr = 0xFFF0 << D_80079980;
    } else {
        remaining = (0x10000 - D_800799C0[voice_or_chunk_size]) << D_80079980;
        spu_addr = D_800799C0[voice_or_chunk_size] << D_80079980;
    }

    saved_busy = D_80079974;
    if (saved_busy == 1) {
        D_80079970[1] = 0;
        restore_busy = 1;
    }

    more_chunks = 1;
    if (D_80079990[0] != 0) {
        pending_swap = D_80079988[2];
        D_8007998C[1] = 0;
    }

    do {
        if ((u32)remaining >= 0x401) {
            voice_or_chunk_size = 0x400;
        } else {
            voice_or_chunk_size = remaining;
            more_chunks = 0;
        }

        func_8005D1D0(2, spu_addr);
        func_8005D1D0(1);
        func_8005D1D0(3, D_80079550, voice_or_chunk_size);
        WaitEvent(D_800794EC);
        remaining -= 0x400;
        spu_addr += 0x400;
    } while (more_chunks);

    if (restore_busy)
        D_80079970[1] = saved_busy;

    if (pending_swap != 0)
        D_80079990[0] = pending_swap;

    return 0;
}

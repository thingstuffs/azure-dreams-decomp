#include "engine/audio/spu/sound_transfer_frontends.h"



/* Starts or restarts channel playback and returns the playback parameter. */
s32 submit_driver_transfer_with_fallback(s32 channel, s32 playback_param)
{
    s32 saved_channel = channel;
    s32 saved_param = playback_param;

    if (spu_transfer_uses_fifo != 0) {
        write_spu_transfer_fifo_in_chunks((u16 *)saved_channel, (u32)saved_param);
        return saved_param;
    }

    dispatch_spu_dma_transfer_command(2, (s32)spu_transfer_address_units << spu_address_unit_shift);
    dispatch_spu_dma_transfer_command(1);
    dispatch_spu_dma_transfer_command(3, saved_channel, saved_param);
    return saved_param;
}

/* Uploads a buffer to the current SPU transfer address and returns its size. */
s32 submit_driver_transfer_mode_zero(s32 buffer_addr, s32 size)
{
    s32 upload_addr = buffer_addr;
    s32 upload_size = size;

    dispatch_spu_dma_transfer_command(2, (s32)spu_transfer_address_units << spu_address_unit_shift);
    dispatch_spu_dma_transfer_command(0);
    dispatch_spu_dma_transfer_command(3, upload_addr, upload_size);

    return upload_size;
}

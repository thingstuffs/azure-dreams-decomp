/* SPU buffer transfers using DMA commands or the transfer-FIFO fallback. */
#include "engine/audio/spu/sound_transfer_frontends.h"
#include "engine/audio/spu.h"



/* Starts or restarts channel playback and returns the playback parameter. */
s32 _spu_Fw(s32 channel, s32 playback_param)
{
    s32 saved_channel = channel;
    s32 saved_param = playback_param;

    if (spu_transfer_uses_fifo != 0) {
        _spu_FwriteByIO((u16 *)saved_channel, (u32)saved_param);
        return saved_param;
    }

    _spu_t(2, (s32)spu_transfer_address_units << spu_address_unit_shift);
    _spu_t(1);
    _spu_t(3, saved_channel, saved_param);
    return saved_param;
}

/* Uploads a buffer to the current SPU transfer address and returns its size. */
s32 _spu_Fr(s32 buffer_addr, s32 size)
{
    s32 upload_addr = buffer_addr;
    s32 upload_size = size;

    _spu_t(2, (s32)spu_transfer_address_units << spu_address_unit_shift);
    _spu_t(0);
    _spu_t(3, upload_addr, upload_size);

    return upload_size;
}

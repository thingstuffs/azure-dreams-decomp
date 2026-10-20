#include "engine/audio/spu/sound_transfer_frontends.h"



/* Starts or restarts channel playback and returns the playback parameter. */
s32 submit_driver_transfer_with_fallback(s32 channel, s32 playback_param)
{
    s32 saved_channel = channel;
    s32 saved_param = playback_param;

    if (D_80079974 != 0) {
        func_8005CE98((u16 *)saved_channel, (u32)saved_param);
        return saved_param;
    }

    func_8005D1D0(2, (s32)D_80079970 << D_80079980);
    func_8005D1D0(1);
    func_8005D1D0(3, saved_channel, saved_param);
    return saved_param;
}

/* Uploads a buffer to the current SPU transfer address and returns its size. */
s32 submit_driver_transfer_mode_zero(s32 buffer_addr, s32 size)
{
    s32 upload_addr = buffer_addr;
    s32 upload_size = size;

    func_8005D1D0(2, (s32)D_80079970 << D_80079980);
    func_8005D1D0(0);
    func_8005D1D0(3, upload_addr, upload_size);

    return upload_size;
}

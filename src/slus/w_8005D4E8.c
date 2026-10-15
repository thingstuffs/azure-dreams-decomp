#include "slus/sound_transfer_frontends.h"

/* Uploads a buffer to the current SPU transfer address and returns its size. */
s32 func_8005D4E8(s32 buffer_addr, s32 size)
{
    s32 upload_addr = buffer_addr;
    s32 upload_size = size;

    func_8005D1D0(2, (s32)D_80079970 << D_80079980);
    func_8005D1D0(0);
    func_8005D1D0(3, upload_addr, upload_size);

    return upload_size;
}

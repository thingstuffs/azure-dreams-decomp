#include "common.h"

#include "engine/audio/slots.h"
#include "engine/audio/ram_block.h"

extern s32 SpuSetReverbModeParam(s32 *request);

/* Submit a value and record it when the request succeeds. */
s16 set_audio_bank(s16 value)
{
    s32 request[6];

    request[0] = 1;
    request[1] = value;
    if (SpuSetReverbModeParam(request) != 0) {
        return -1;
    }
    sound_ram_reserve_mode[0] = value;
    return value;
}

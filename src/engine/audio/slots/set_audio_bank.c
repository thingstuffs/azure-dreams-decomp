#include "common.h"

#include "common.h"
#include "engine/audio/slots.h"

extern s32 func_8005DA88(s32 *request);
extern s8 sound_ram_reserve_mode[9];

/* Submit a value and record it when the request succeeds. */
s16 set_audio_bank(s16 value)
{
    s32 request[6];

    request[0] = 1;
    request[1] = value;
    if (func_8005DA88(request) != 0) {
        return -1;
    }
    sound_ram_reserve_mode[0] = value;
    return value;
}

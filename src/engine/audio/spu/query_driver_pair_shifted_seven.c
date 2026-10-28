#include "common.h"
#include "engine/audio/spu.h"



extern s32 audio_voice_masks[];

/* Computes two outputs from indexed flags, scales them down by 128, and returns zero. */
s32 query_driver_pair_shifted_seven(s16 flags_index, s16 *out_first, s16 *out_second)
{
    SpuVoiceAttr_ request;

    request.mask = 0;
    request.voice = audio_voice_masks[flags_index];
    SpuGetVoiceAttr(&request);
    *out_first = request.volume.left >> 7;
    *out_second = request.volume.right >> 7;
    return 0;
}

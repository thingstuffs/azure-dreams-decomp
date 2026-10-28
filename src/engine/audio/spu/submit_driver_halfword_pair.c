#include "common.h"
#include "engine/audio/spu.h"

/* Request struct passed to func_8005F134 (an ~0x40-byte object; here only
 * flags word (offset 0), type/count word (offset 4), and two s16 params
 * (offsets 8/0xA) are initialized -- the rest is left as stack garbage). */

extern s32 audio_voice_masks[];

/* Sends a type-3 request with indexed flags and two s16 parameters, then returns zero. */
s32 submit_driver_halfword_pair(s16 flags_index, s16 first_value, s16 second_value)
{
    SpuVoiceAttr_ request;

    request.mask = 3;
    request.voice = *(&audio_voice_masks[flags_index]);
    request.volume.left = first_value;
    request.volume.right = second_value;
    apply_spu_voice_attributes(&request);
    return 0;
}

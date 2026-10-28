#include "common.h"
#include "engine/audio/spu.h"

/* struct passed to func_8005F134: flags word, count word, an unused word,
 * then two packed 16-bit fields; the (0x40-byte) struct's remaining tail is
 * padding never touched here. Only the fields this function sets are
 * known/used. */

extern s32 audio_voice_masks[24];

/* Dispatches an effect request with table flags, count 3, and two scaled 7-bit values. */
s32 submit_driver_seven_bit_pair(s32 flag_index, s32 first_value, s32 second_value)
{
    SpuVoiceAttr_ request;
    s32 flags;

    request.mask = 3;
    flags = audio_voice_masks[(s16)flag_index];
    request.volume.left = (first_value & 0x7F) << 7;
    request.volume.right = (second_value & 0x7F) << 7;
    request.voice = flags;

    apply_spu_voice_attributes(&request);

    return 0;
}

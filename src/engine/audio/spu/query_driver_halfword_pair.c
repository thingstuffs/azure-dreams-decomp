#include "common.h"
#include "engine/audio/spu.h"

extern s32 audio_voice_masks[24];



/* Processes the indexed table entry and copies the two request results to the output pointers. */
s32 query_driver_halfword_pair(s16 entry_index, s16 *out_first_value, s16 *out_second_value) {
    SpuVoiceAttr_ request;

    request.mask = 0;
    request.voice = audio_voice_masks[entry_index];
    SpuGetVoiceAttr(&request);
    *out_first_value = request.volume.left;
    *out_second_value = request.volume.right;
    return 0;
}

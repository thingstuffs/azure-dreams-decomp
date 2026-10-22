#include "common.h"
#include "engine/audio/spu.h"

/* Request/response struct passed to func_8005FA34: caller pre-fills unk0
 * (flags from D_80073740[idx]) and zeroes unk4; callee writes back two
 * s16 outputs at unk8/unkA which the caller rescales (>>7) into *a1/*a2. */
typedef struct S_8005C784 {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    u8 pad[0x40 - 0xC];
} S_8005C784;

extern s32 audio_voice_masks[];

/* Computes two outputs from indexed flags, scales them down by 128, and returns zero. */
s32 query_driver_pair_shifted_seven(s16 flags_index, s16 *out_first, s16 *out_second)
{
    S_8005C784 request;

    request.unk4 = 0;
    request.unk0 = audio_voice_masks[flags_index];
    SpuGetVoiceAttr(&request);
    *out_first = request.unk8 >> 7;
    *out_second = request.unkA >> 7;
    return 0;
}

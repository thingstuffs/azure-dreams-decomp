#include "common.h"
#include "engine/audio/sequence.h"

/* Inferred struct for global D_80084918, reconciled across this wave's siblings. */
typedef struct {
    /* 0x00 */ s32 field0;
    /* 0x04 */ u32 field4;
    /* 0x08 */ u8  pad08[0x24 - 0x08];
    /* 0x24 */ s32 field24;
    /* 0x28 */ u8  pad28[0x3A - 0x28];
    /* 0x3A */ u16 field3A;
    /* 0x3C */ u16 field3C;
} S_80084918;

extern S_80084918 audio_voice_request;
extern s32 audio_voice_masks[];


extern s32 apply_spu_voice_attributes(S_80084918 *descriptor);

/* Populates the global descriptor from a table entry and source fields, then processes it. */
s32 sound_apply_indexed_voice_envelope(s32 table_index, SoundVoiceRecord *source) {
    S_80084918 *descriptor = &audio_voice_request;
    descriptor->field4 = 0x60100;
    audio_voice_request.field0 = audio_voice_masks[table_index];
    descriptor->field3A = source->field60;
    descriptor->field3C = source->field64;
    descriptor->field24 = source->field68;
    return apply_spu_voice_attributes(descriptor);
}

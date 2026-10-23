#include "common.h"
#include "engine/audio/sequence.h"

typedef struct S_80084918 {
    /* 0x0 */ s32 field0;
    /* 0x4 */ s32 field4;
    /* 0x8 */ s16 field8;
    /* 0xA */ s16 fieldA;
    /* 0xC */ s16 fieldC;
    /* 0xE */ s16 fieldE;
} S_80084918;

extern S_80084918 audio_voice_request;
extern s32 audio_voice_masks[];

extern s32 apply_spu_voice_attributes(S_80084918 *arg);

/*
 * Builds audio_voice_request from the indexed voice mask and two volume fields with attribute mask
 * 15, then returns the SPU attribute update result.
 */
s32 sound_set_indexed_voice_volumes(s32 table_index, s16 field_8_value, s16 field_a_value) {
    S_80084918 *record = &audio_voice_request;
    s32 table_value;

    record->field4 = 15;
    table_value = audio_voice_masks[table_index];
    record->field8 = field_8_value;
    record->fieldA = field_a_value;
    record->fieldC = 0;
    record->fieldE = 0;
    record->field0 = table_value;
    return apply_spu_voice_attributes(record);
}

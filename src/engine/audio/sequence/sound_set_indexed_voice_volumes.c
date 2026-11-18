#include "common.h"
#include "slus/audio_voice_data.h"
#include "engine/audio/sequence.h"
#include "engine/audio/spu.h"

/* Apply the left and right volumes with both volume modes cleared. */
void sound_set_indexed_voice_volumes(s32 table_index, s32 left_volume, s32 right_volume) {
    SpuVoiceAttr_ *record = &audio_voice_request;
    s32 table_value;

    record->mask = 15;
    table_value = audio_voice_masks[table_index];
    record->volume.left = left_volume;
    record->volume.right = right_volume;
    record->volmode.left = 0;
    record->volmode.right = 0;
    record->voice = table_value;
    apply_spu_voice_attributes(record);
}

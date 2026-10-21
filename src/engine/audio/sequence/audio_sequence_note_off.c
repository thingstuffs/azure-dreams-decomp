#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"



typedef struct {
    u8 pad00[6];
    u16 field06;
    u8 pad08[2];
    u16 field0A;
    u8 pad0C[0x1A - 0x0C];
    s16 field1A;
    u8 field1C;
    u8 field1D;
    u8 pad1E[0x78 - 0x1E];
} S_80085458;

extern s32 audio_voice_count[];
extern s32 audio_voice_masks[];
extern S_80085458 audio_voice_records[];

extern s32 sound_apply_indexed_voice_envelope();

#define ACTIVE_COUNT (*(s32 *)0x80073734)

/* Process active records matching both key bytes and combine their masks. */
void audio_sequence_note_off(s32 first_key, s32 second_key) {
    S_80085458 *record;
    s32 *mask_entry;
    s32 record_mask;
    s32 record_index;
    s32 second_byte;
    s32 combined_mask;
    s32 first_byte;

    record_index = 0;
    combined_mask = 0;
    if (ACTIVE_COUNT > 0) {
        first_byte = first_key & 0xFF;
        second_byte = second_key & 0xFF;
        mask_entry = audio_voice_masks;
        do {
            record = &audio_voice_records[record_index];
            if ((first_byte == record->field06) &&
                (second_byte == record->field0A)) {
                if (record->field1D == 0) {
                    sound_apply_indexed_voice_envelope(record_index, record);
                    record_mask = *mask_entry;
                    combined_mask |= record_mask;
                    set_spu_voice_keys(0, record_mask);
                    record->field1A = 0;
                } else {
                    record->field1C |= 0x80;
                }
            }
            mask_entry++;
        } while (++record_index < ACTIVE_COUNT);
    }
    if (combined_mask != 0) {
        do {
            set_spu_voice_keys(0, combined_mask);
        } while (0);
    }
}

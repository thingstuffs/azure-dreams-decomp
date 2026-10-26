#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

/* D_80085458 table element, stride 0x78 bytes. Fields at 0x0A and 0x5C are
 * newly touched here (not referenced by other reconciled siblings); rest of
 * the layout matches the canonical struct established in src/w_80056A08.c
 * and friends. */
typedef SoundVoiceRecord S_8005BAB0_85458;

extern s32 audio_voice_count[4];
extern s32 audio_voice_masks[24];
extern S_8005BAB0_85458 audio_voice_records[24];
extern s32 audio_update_guard[4]; /* forced hi/lo access via size > 8 */


/* Clears matching active indirect-channel slots, redispatches each twice, and applies their combined flags. */
void audio_stop_matching_effect_voices(s32 packed_key, s32 packed_channel)
{
    S_8005BAB0_85458 *slot;
    s32 *slot_flags;
    s32 combined_flags;
    s32 slot_index;

    slot_index = 0;
    combined_flags = slot_index;
    audio_update_guard[0] = 1;

    if (audio_voice_count[0] > 0) {
        slot_flags = audio_voice_masks;
        slot = audio_voice_records;
loop:
        if (slot->field1A != 0 && (u16)slot->field06 >= 0x10 && slot->field0A == (packed_channel >> 8) &&
            slot->field5C == (packed_key >> 8) && slot->field04 == (u16)(packed_key & 0x7F)) {
            combined_flags |= *slot_flags;
            slot->field1A = 0;
            slot->field0A = 0;
            sound_apply_indexed_voice_envelope(slot_index, slot);
            SpuSetKey(0, *slot_flags);
            sound_apply_indexed_voice_envelope(slot_index, slot);
            SpuSetKey(0, *slot_flags);
            combined_flags |= *slot_flags;
        }
        slot_flags++;
        slot++;
        slot_index++;
        if (slot_index < audio_voice_count[0]) {
            goto loop;
        }
    }

    SpuSetKey(0, combined_flags);
    audio_update_guard[0] = 0;
}

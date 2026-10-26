#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/audio/spu.h"
#include "slus.h"

typedef SoundVoiceRecord S_80085458;

extern S_80085458 audio_voice_records[24];
extern s32 audio_voice_masks[];
extern s32 audio_update_guard[3];


/* Services an active SPU slot until completion and clears the busy flag. */
s32 audio_stop_effect_voice(s16 slot_id)
{
    u8 *busy_or_slot = (u8 *)audio_update_guard;
    u8 *slots = (u8 *)audio_voice_records;
    s32 slot_index = slot_id;
    s32 slot_handle;
    u8 *slot;
    s32 status;
    u16 active;

    slot = slots + slot_index * 0x78;
    active = *(u16 *)(slot + 0x1A);
    *(s32 *)busy_or_slot = 1;
    if (!(active == 0 || *(u16 *)(slot + 6) < 0x10)) {
        slot_handle = audio_voice_masks[slot_index];
        busy_or_slot = slot;
        *(u16 *)(busy_or_slot + 0x1A) = 0;
        *(u16 *)(busy_or_slot + 0x0A) = 0;
        sound_apply_indexed_voice_envelope(slot_index, (S_80085458 *)busy_or_slot);
        sound_reset_indexed_voice_envelope(slot_index);
        SpuSetKey(0, audio_voice_masks[slot_index]);
        do {
            SpuSetKey(0, slot_handle);
            status = SpuGetKeyStatus(slot_handle);
            if (status == 2) {
                break;
            }
        } while (status != 0);
    } else {
        audio_update_guard[0] = 0;
        return -1;
    }
    audio_update_guard[0] = 0;
    return 0;
}

#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/audio/spu.h"


extern s32 audio_voice_count[4];
extern s32 audio_voice_masks[24];
extern s32 audio_sequence_active[4];
extern u8 audio_voice_records[0x78 * 24];
extern s32 audio_update_guard[4];
extern SoundSequenceSlot audio_sequence_slots[8];

/* Process eligible entries and set the selected slot state to 4. */
void suspend_sequence_slot(s16 slot_index)
{
    SpuVoiceAttr_ request;
    u8 *entry;
    s32 entry_index;
    s32 *entry_id;
    SoundSequenceSlot *slots;

    entry_index = 0;
    audio_update_guard[0] = 1;
    if (audio_voice_count[0] > 0) {
        entry_id = audio_voice_masks;
        entry = audio_voice_records;
loop:
        if (*(u16 *)(entry + 6) < 0x10U) {
            if (*(u16 *)(entry + 0x1A) != 0) {
                s32 request_type;
                request_type = 3;
                request.mask = request_type;
                request.voice = *entry_id;
                request.volume.left = 0;
                request.volume.right = 0;
                apply_spu_voice_attributes(&request);
            }
        }
        entry_id++;
        entry += 0x78;
        {
            s32 entry_count = audio_voice_count[0];
            /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: slus/w_8005B070). */
            do {
                entry_index++;
            } while (0);
            if (entry_index < entry_count)
                goto loop;
        }
    }
    slots = audio_sequence_slots;
    slots[slot_index].state = 4;
    audio_update_guard[0] = 0;
    audio_sequence_active[0] = 0;
}

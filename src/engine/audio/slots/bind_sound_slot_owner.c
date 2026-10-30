#include "common.h"

#include "common.h"
#include "engine/audio/slots.h"
#include "engine/audio/spu.h"

typedef struct {
    s16 marker;
    u8 pad02[0x0A];
    s32 owner;
    s32 unk10;
    s32 unk14;
    u8 pad18[4];
} S_80086A40; /* size 0x1C */

extern S_80086A40 audio_bank_slots[];

/* Upload a sound slot's body to sound RAM and record its owner when the marker matches and the whole body transfers. */
s16 transfer_sound_slot_body_to_spu(s32 owner, s16 entry_id)
{
    s32 updated_value;
    s16 marker;
    S_80086A40 *entries;
    S_80086A40 *entry;

    entries = audio_bank_slots;
    entry = &entries[entry_id];
    marker = entry->marker;
    if (marker == entry_id) {
        updated_value = SpuSetTransferStartAddr(entry->unk10);
        if (write_spu_transfer_data(owner, entry->unk14) == entry->unk14) {
            entry->owner = owner;
            entry->unk10 = updated_value;
            return marker;
        }
        return -1;
    }
    return -1;
}

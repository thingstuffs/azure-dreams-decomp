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

/* Assigns an owner and updates the entry value when its marker matches and its transfer size is accepted. */
s16 bind_sound_slot_owner(s32 owner, s16 entry_id)
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
        if (clamp_and_submit_driver_parameter(owner, entry->unk14) == entry->unk14) {
            entry->owner = owner;
            entry->unk10 = updated_value;
            return marker;
        }
        return -1;
    }
    return -1;
}

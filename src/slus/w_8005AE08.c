#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

/* Sound driver "sequence slot" table; 8 entries, 12 bytes each. */

extern SoundSequenceSlot audio_sequence_slots[8];

/* Registers a recognized sequence header in the first free slot, returning its index or -1 on failure. */
s16 allocate_sequence_bank_slot(void *header, s32 sequence_id)
{
    u32 magic = *(u32 *)header;
    SoundSequenceSlot *slot;
    s32 slot_index;
    s32 free_id;

    if (magic != 0x53455170 && magic != 0x6468544D && magic != 0x2054444B) {
        return -1;
    }
    slot_index = 0;
    free_id = -1;
    slot = audio_sequence_slots;
    while (slot_index < 8) {
        if (slot->sequence_id == free_id) {
            slot->data_address = header;
            slot->sequence_id = sequence_id;
            slot->state = 2;
            return slot_index;
        }
        slot_index++;
        slot++;
    }
    return -1;
}

#include "common.h"

#include "common.h"

s32 read_sound_payload_slot();                                /* extern */
extern s32 audio_bank_owner_payloads[];
extern s32 sequence_payload_slot_18[];
extern s32 sequence_payload_slot_20[];
extern s32 sequence_payload_slot_24[];

/* Store the fetched value in the global selected by the low 16 bits. */
void sound_assign_sequence_payload_slot(s32 selector) {
    s32 slot_id;
    s32 value;

    value = read_sound_payload_slot();
    slot_id = selector & 0xFFFF;
    switch (slot_id) {                              /* irregular */
    case 17:
        audio_bank_owner_payloads[0] = value;
        return;
    case 18:
        sequence_payload_slot_18[0] = value;
        return;
    case 20:
        sequence_payload_slot_20[0] = value;
        return;
    case 24:
        sequence_payload_slot_24[0] = value;
        return;
    }
}

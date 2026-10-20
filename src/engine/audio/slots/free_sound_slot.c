#include "common.h"

/* 0x1C-byte-stride slot table shared with audio_get_current_bank_tone_record (D_80086A40). This
 * function clears a slot: if the slot's s16 marker (offset 0x00) is not -1,
 * it calls release_sound_ram_block with the slot's data pointer (offset 0x10), then
 * marks the slot free by setting the marker to -1. */
typedef struct {
    /* 0x00 */ s16 marker;
    /* 0x02 */ u8 pad02[2];
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u8 pad08[8];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[8];
} S_8005AC68; /* size 0x1C (28) */

extern S_8005AC68 D_80086A40[16];

extern void release_sound_ram_block(s32 addr);

/* Releases an occupied slot's data and marks the slot free. */
void free_sound_slot(s16 slot_index) {
    S_8005AC68 *slots = D_80086A40;
    S_8005AC68 *slot = &slots[slot_index];
    s16 free_marker = -1;

    if (free_marker != slot->marker) {
        release_sound_ram_block(slot->unk10);
        slot->marker = free_marker;
    }
}

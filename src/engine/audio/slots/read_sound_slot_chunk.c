#include "common.h"

#include "common.h"

typedef struct {
    /* 0x00 */ s16 marker;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} S_80086A40;

extern S_80086A40 audio_bank_slots[16];
typedef struct {
    s32 value;
    s32 pad[2];
} S_8007382C;

extern S_8007382C sound_slot_transfer_cursor;

extern s32 clamp_and_submit_driver_parameter(s32 dest, u32 size);
extern void lookup_and_scale_driver_address(s32 value);

/* Reads a bounded chunk from the selected entry and advances its cursor. */
s32 read_sound_slot_chunk(s32 dest, u32 read_size, s16 entry_id)
{
    S_80086A40 *base;
    S_80086A40 *entry;
    u32 remaining;

    base = audio_bank_slots;
    entry = &base[entry_id];

    if (entry->marker != entry_id) {
        return -1;
    }

    lookup_and_scale_driver_address(entry->unk10 + sound_slot_transfer_cursor.value);

    remaining = entry->unk14 - sound_slot_transfer_cursor.value;
    if (remaining < read_size) {
        read_size = remaining;
    }

    if (clamp_and_submit_driver_parameter(dest, read_size) != read_size) {
        return -1;
    }

    {
        s32 new_cursor;
        s32 end;
        new_cursor = sound_slot_transfer_cursor.value + read_size;
        end = entry->unk14;
        sound_slot_transfer_cursor.value = new_cursor;
        if (new_cursor >= end) {
            return entry_id;
        }
        return -2;
    }
}

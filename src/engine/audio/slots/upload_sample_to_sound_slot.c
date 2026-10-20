#include "common.h"

typedef struct {
    /* 0x00 */ s16 marker;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
} S_80086A40;

extern S_80086A40 D_80086A40[16];
extern s32 D_8007382C[3]; /* size > 8: forced hi/lo, no $gp */

extern void release_sound_ram_block(s32);
extern s32 reserve_sound_ram_block(s32, s32);
extern s32 lookup_and_scale_driver_address(s32);
extern s32 clamp_and_submit_driver_parameter(s32, u32);

/* Reserves a sound slot and transfers sample data to the requested sound RAM address. */
s32 upload_sample_to_sound_slot(s32 src_addr, s32 sound_addr, s32 size, s16 requested_slot)
{
    s16 slot_id;
    s16 selected_slot;
    s32 slot_index;
    S_80086A40 *slot;
    s32 reserved_addr;

    D_8007382C[0] = 0;
    slot_id = 0;
    selected_slot = requested_slot;
    if (selected_slot == -1) {
        while (1) {
            if (D_80086A40[slot_id].marker == -1) {
                break;
            }
            slot_id = slot_id + 1;
            if (slot_id >= 16) {
                return -1;
            }
        }
    } else {
        slot_id = selected_slot;
        if (D_80086A40[slot_id].marker != -1) {
            release_sound_ram_block(D_80086A40[slot_id].unk10);
        }
    }
    slot_index = slot_id;
    slot = &D_80086A40[slot_index];
    slot->unk14 = size;
    slot->marker = slot_id;
    slot->unk04 = src_addr;
    slot->unk08 = size;
    slot->unk18 = 0x7F;
    slot->unk1B = 0x40;
    slot->unk10 = sound_addr;
    reserved_addr = reserve_sound_ram_block(sound_addr, slot->unk14);
    slot->unk10 = reserved_addr;
    if (reserved_addr == -1) {
        return -1;
    }
    sound_addr = lookup_and_scale_driver_address(reserved_addr);
    size = clamp_and_submit_driver_parameter(src_addr, slot->unk14);
    if (size != slot->unk14) {
        return -1;
    }
    slot->unk0C = src_addr;
    slot->unk10 = sound_addr;
    return slot_index;
}

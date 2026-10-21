/* Occupied slot window; G00386; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_800105A0, CL:main/func_80010B18, CL:main/func_80010C44, CL:main/func_80010D64. */
#include "frontend/libcard/occupied_slot_window_g00386.h"
#include "frontend/libcard.h"

/* Initialize four message slots with their data and command parameters. */
void card_boot_format_occupied_slot_window(void *slot_owner) {
    s32 data_buffer[2];
    Slot80010C44 *slot;

    slot = *(Slot80010C44 **) ((u8 *) slot_owner + 0x270);
    slot->msg->cmd = 0x70;
    slot->msg->arg = 0x10;
    slot->data = &D_80078FD0;

    slot = *(Slot80010C44 **) ((u8 *) slot_owner + 0x260);
    slot->data = (void *) decode_fullwidth_text((u8 *) slot_owner + 8, card_slot_payload + (*(s32 *) slot_owner << 7), 1);
    slot->msg->cmd = 0xF0;
    slot->msg->arg = 0x91;

    slot = *(Slot80010C44 **) ((u8 *) slot_owner + 0x26C);
    func_8004E5A0((void *) *(s32 *) (card_slot_payload + (*(s32 *) slot_owner << 7) + 0x20), 4, data_buffer);
    remap_flagged_string_bytes(data_buffer);
    slot->data = (void *) build_positioned_text_glyphs((u8 *) slot_owner + 0x104, data_buffer, 1);
    slot->msg->cmd = 0x147;
    slot->msg->arg = 0x91;

    slot = *(Slot80010C44 **) ((u8 *) slot_owner + 0x278);
    slot->data = (u8 *) slot_owner + 0x134;
    slot->msg->cmd = 0xAE;
    slot->msg->arg = 0x18;
}

/* Initialize data pointers and layout values for three targets. */
void card_boot_layout_alternate_slot_window(void *context) {
    UnkTarget *target;

    target = *(UnkTarget **)((u8 *)context + 0x274);
    target->unk4->unk8 = 0xFA;
    target->unk4->unkA = 0x10;
    target->unk0 = &D_80027F7C;

    target = *(UnkTarget **)((u8 *)context + 0x268);
    target->unk0 = (void *) decode_fullwidth_text((u8 *)context + 0xA4, (u8 *)&D_800282B0, 1);
    target->unk4->unk8 = 0x178;
    target->unk4->unkA = 0x90;

    target = *(UnkTarget **)((u8 *)context + 0x27C);
    target->unk0 = (u8 *)context + 0x1AC;
    target->unk4->unk8 = 0x10C;
    target->unk4->unkA = 0x18;
}

/* Processes two buffers and selects handlers using the state's indexed entry. */
void card_boot_populate_slot_window_display(s32 *state) {
    func_80023BE4((u8 *)state + 0x134, 0x80, 0x18);
    func_80023BE4((u8 *)state + 0x1AC, 0x2A, 0x14);
    if (card_save_slot_metadata[*state].unk0 != 0) {
        card_boot_format_occupied_slot_window(state);
        if (card_save_slot_metadata[*state].unk8 != 0) {
            card_boot_layout_alternate_slot_window(state);
            return;
        }
    } else {
        card_boot_layout_empty_slot_window(state);
    }
}

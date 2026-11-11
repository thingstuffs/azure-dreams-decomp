/* Occupied slot window; G00386; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_800105A0, CL:main/func_80010B18, CL:main/func_80010C44, CL:main/func_80010D64. */
#include "frontend/libcard/occupied_slot_window_g00386.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "engine/audio/sequence.h"
#include "engine/text.h"

/* Initialize four message slots with their data and command parameters. */
void card_boot_format_occupied_slot_window(void *slot_owner) {
    s32 data_buffer[2];
    CardMenuDisplayNode *slot;

    slot = *(CardMenuDisplayNode **) ((u8 *) slot_owner + 0x270);
    slot->block->fields.x = 0x70;
    slot->block->fields.y = 0x10;
    slot->payload.data = &D_80078FD0;

    slot = *(CardMenuDisplayNode **) ((u8 *) slot_owner + 0x260);
    slot->payload.data = decode_fullwidth_text((u8 *) slot_owner + 8, card_slot_payload + (*(s32 *) slot_owner << 7), 1);
    slot->block->fields.x = 0xF0;
    slot->block->fields.y = 0x91;

    slot = *(CardMenuDisplayNode **) ((u8 *) slot_owner + 0x26C);
    func_8004E5A0((void *) *(s32 *) (card_slot_payload + (*(s32 *) slot_owner << 7) + 0x20), 4, data_buffer);
    remap_flagged_string_bytes(data_buffer);
    slot->payload.data = build_positioned_text_glyphs((u8 *) slot_owner + 0x104, data_buffer, 1);
    slot->block->fields.x = 0x147;
    slot->block->fields.y = 0x91;

    slot = *(CardMenuDisplayNode **) ((u8 *) slot_owner + 0x278);
    slot->payload.data = (u8 *) slot_owner + 0x134;
    slot->block->fields.x = 0xAE;
    slot->block->fields.y = 0x18;
}

/* Initialize data pointers and layout values for three targets. */
void card_boot_layout_alternate_slot_window(void *context) {
    CardMenuDisplayNode *target;

    target = *(CardMenuDisplayNode **)((u8 *)context + 0x274);
    target->block->fields.x = 0xFA;
    target->block->fields.y = 0x10;
    target->payload.data = &D_80027F7C;

    target = *(CardMenuDisplayNode **)((u8 *)context + 0x268);
    target->payload.data = decode_fullwidth_text((u8 *)context + 0xA4, (u8 *)&D_800282B0, 1);
    target->block->fields.x = 0x178;
    target->block->fields.y = 0x90;

    target = *(CardMenuDisplayNode **)((u8 *)context + 0x27C);
    target->payload.data = (u8 *)context + 0x1AC;
    target->block->fields.x = 0x10C;
    target->block->fields.y = 0x18;
}

/* Processes two buffers and selects handlers using the state's indexed entry. */
void card_boot_populate_slot_window_display(CardSlotWindow *window) {
    func_80023BE4(window->wide_panel, 0x80, 0x18);
    func_80023BE4(window->small_panel, 0x2A, 0x14);
    if (card_save_slot_metadata[window->slot_index].words[0] != 0) {
        card_boot_format_occupied_slot_window(window);
        if (card_save_slot_metadata[window->slot_index].halfwords[4] != 0) {
            card_boot_layout_alternate_slot_window(window);
            return;
        }
    } else {
        card_boot_layout_empty_slot_window(window);
    }
}

#include "common.h"

extern void *D_800282A4[3];
extern void *D_800791A4;

extern s32 card_boot_get_remaining_block_summary(void);
extern void *decode_note_text(void *, void *, s32);

/* Initializes resources and screen positions for three display entries. */
void card_boot_layout_empty_slot_window(void *object) {
    void **display_entry;
    s32 resource_index;

    display_entry = *(void ***)((u8 *) object + 0x260);
    resource_index = (card_boot_get_remaining_block_summary() >= 3);
    *(void **) display_entry = decode_note_text((u8 *) object + 8, D_800282A4[resource_index], 1);
    *(s16 *)((u8 *) display_entry[1] + 8) = 0xF0;
    *(s16 *)((u8 *) display_entry[1] + 0xA) = 0x91;

    display_entry = *(void ***)((u8 *) object + 0x270);
    *(s16 *)((u8 *) display_entry[1] + 8) = 0x70;
    *(s16 *)((u8 *) display_entry[1] + 0xA) = 0x10;
    *(void **) display_entry = &D_800791A4;

    display_entry = *(void ***)((u8 *) object + 0x278);
    *(void **) display_entry = (u8 *) object + 0x134;
    *(s16 *)((u8 *) display_entry[1] + 8) = 0xAE;
    *(s16 *)((u8 *) display_entry[1] + 0xA) = 0x18;
}

#include "common.h"

typedef s32 M2C_UNK;

extern void *card_boot_recheck_selected_channel(void);
extern s32 card_boot_write_save_via_temporary_path(s32, s32);
extern void card_boot_show_overwrite_failure_notice(void *);
extern void card_boot_set_slot_selection_marker(s32, s32);
extern void card_boot_set_slot_details_selection(s32, s32, s32);
extern void card_boot_prepare_save_buffer(s32, s32, s32);
extern void card_boot_refresh_five_slot_objects(void *);
extern M2C_UNK SD_Call(s32);
extern M2C_UNK configure_shared_fade_primitive(void);

extern s16 D_80010208[];
extern M2C_UNK D_800261C0[];
extern M2C_UNK D_80026240[];
extern s32 D_800265B8[];


/* Processes the current selection and stores the next state. */
void *card_boot_save_selected_slot(void *context) {
    void *result;

    card_boot_prepare_save_buffer(0x80010000, *(s32 *)((s8 *)context + 0x2C), *(s32 *)((s8 *)context + 0x24));
    if (card_boot_write_save_via_temporary_path(*(s32 *)((s8 *)context + 0x2C), 0x80010000) == 0) {
        *(u8 **)((s8 *)context + 0x34) = (u8 *)D_800265B8;
        card_boot_show_overwrite_failure_notice((u8 *)context - 0x20);
        *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_800261C0;
    } else {
        card_boot_set_slot_details_selection(*(s32 *)((s8 *)context + 4), *(s32 *)((s8 *)context + 0x2C), 3);
        card_boot_refresh_five_slot_objects(context);
        card_boot_set_slot_selection_marker(*(s32 *)((s8 *)context + *(s32 *)((s8 *)context + 0x2C) * 4 + 0xC), 1);
        if (D_80010208[0] != 0) {
            configure_shared_fade_primitive();
            *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_80026240;
        } else {
            SD_Call(0x503);
            *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_800265B8;
        }
    }
    result = card_boot_recheck_selected_channel();
    *(s32 *)((s8 *)context + 0x40) = 0;
    return result;
}

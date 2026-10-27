#include "common.h"
#include "frontend/libcard/message.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/libcard.h"
#include "main/data.h"
#include "slus.h"

extern void *card_boot_recheck_selected_channel(void);
extern void card_boot_prepare_save_buffer(s32, s32, s32);
void configure_shared_fade_primitive(void);

extern s16 D_80010208[];

/* Processes the current selection and stores the next state. */
void *card_boot_save_selected_slot(void *context) {
    void *result;

    card_boot_prepare_save_buffer(0x80010000, *(s32 *)((s8 *)context + 0x2C), *(s32 *)((s8 *)context + 0x24));
    if (card_boot_write_save_via_temporary_path(*(s32 *)((s8 *)context + 0x2C), 0x80010000) == 0) {
        *(u8 **)((s8 *)context + 0x34) = (u8 *)write_text_and_advance_selection;
        card_boot_show_overwrite_failure_notice((u8 *)context - 0x20);
        *(u8 **)((s8 *)context - 0x10) = (u8 *)&D_800261C0;
    } else {
        card_boot_set_slot_details_selection(*(void **)((s8 *)context + 4), *(s32 *)((s8 *)context + 0x2C), 3);
        card_boot_refresh_five_slot_objects(context);
        card_boot_set_slot_selection_marker(*(s32 *)((s8 *)context + *(s32 *)((s8 *)context + 0x2C) * 4 + 0xC), 1);
        if (D_80010208[0] != 0) {
            configure_shared_fade_primitive();
            *(u8 **)((s8 *)context - 0x10) = (u8 *)&inventory_copy_and_sign_extend_record_fields;
        } else {
            SD_Call(0x503);
            *(u8 **)((s8 *)context - 0x10) = (u8 *)write_text_and_advance_selection;
        }
    }
    result = card_boot_recheck_selected_channel();
    *(s32 *)((s8 *)context + 0x40) = 0;
    return result;
}

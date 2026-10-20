#include "common.h"



#include "modules/main_server_ship_interfaces.h"
extern s32 card_boot_write_save_via_temporary_path(s32, s32);
extern s32 card_boot_load_save_and_clear_marker(s32, s32, s32);
extern void card_boot_show_copy_failure_notice(void *);
extern void card_boot_refresh_slot_window(s32);
#include "frontend/libcard/interfaces.h"
extern void no_op_card_hook(s32);
extern void initialize_save_description(s32, s32);

extern u8 D_80024F7C[];

typedef struct S_80025398_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    s32 unk_2C;
    u8 pad_30[0x10];
    s32 unk_40;
} S_80025398_0;   /* arg0 in process_five_context_entries_or_fallback */

typedef struct S_80025398_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80025398_1;

/* Process five context entries if checks pass, or schedule the fallback callback. */
void process_five_context_entries_or_fallback(void *context) {
    s32 entry_value;
    s32 entry_count;
    void *owner;
    void *entry_cursor;

    if (card_boot_load_save_and_clear_marker(((S_80025398_0 *)context)->unk_2C, 0x80010000, 0) != 0) {
        initialize_save_description(0x80010000, ((S_80025398_0 *)context)->unk_28);
        if (card_boot_write_save_via_temporary_path(((S_80025398_0 *)context)->unk_28, 0x80010000) != 0) {
            no_op_card_hook(0x80010000);
            entry_count = 0;
            card_boot_refresh_directory_summary();
            entry_cursor = context;
            do {
                entry_value = ((S_80025398_1 *)entry_cursor)->unk_04;
                entry_cursor = (u8 *)entry_cursor + 4;
                entry_count += 1;
                card_boot_refresh_slot_window(entry_value);
            } while (entry_count < 5);
            card_boot_resume_menu_after_slot_refresh(context);
            card_boot_recheck_selected_channel();
            ((S_80025398_0 *)context)->unk_40 = 0;
            return;
        }
    }
    owner = (u8 *)context - 0x20;
    *(void (**)(void))((u8 *)context + 0x34) = (void (*)(void))card_boot_resume_menu_after_slot_refresh;
    card_boot_show_copy_failure_notice(owner);
    *(void **)((u8 *)context - 0x10) = (void *)D_80024F7C;
    card_boot_recheck_selected_channel();
    ((S_80025398_0 *)context)->unk_40 = 0;
}

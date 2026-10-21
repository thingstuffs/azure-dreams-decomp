/* Save copy completion; G00392; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_80012358. */
#include "frontend/card/save_copy_completion_g00392.h"

void initialize_save_description(void *owner, s32 value) { card_boot_build_save_description(owner, value); initialize_text_editor_context(owner, value); }

/* Process five context entries if checks pass, or schedule the fallback callback. */
void process_five_context_entries_or_fallback(void *context) {
    s32 entry_value;
    s32 entry_count;
    void *owner;
    void *entry_cursor;

    if (card_boot_load_save_and_clear_marker(((S_80025398_0 *)context)->unk_2C, 0x80010000, 0) != 0) {
        initialize_save_description((void *)0x80010000, ((S_80025398_0 *)context)->unk_28);
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

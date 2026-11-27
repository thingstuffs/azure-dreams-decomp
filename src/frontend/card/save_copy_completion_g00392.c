/* Save copy completion; G00392; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_80012358. */
#include "frontend/card/save_copy_completion_g00392.h"
#include "frontend/libcard_callbacks_api.h"
#include "shared/object_node.h"

/* Write the title and icon for the selected slot into the same save image. */
void initialize_save_description(struct CardSaveImage *save, s32 value)
{
    card_boot_build_save_description(save, value);
    card_boot_store_save_icon_clut_and_frames(save, value);
}

/* Process five context entries if checks pass, or schedule the fallback callback. */
void write_save_and_refresh_slot_windows(CardSlotMenuState *context) {
    ObjectNodeHeader *window;
    s32 entry_count;

    if (card_boot_load_save_and_clear_marker(context->copy_source_slot, 0x80010000, 0) != 0) {
        initialize_save_description((struct CardSaveImage *)0x80010000, context->selected_slot);
        if (card_boot_write_save_via_temporary_path(context->selected_slot, 0x80010000) != 0) {
            no_op_card_hook(0x80010000);
            entry_count = 0;
            card_boot_refresh_directory_summary();
            do {
                window = context->slots[entry_count];
                entry_count += 1;
                card_boot_refresh_slot_window(window);
            } while (entry_count < 5);
            card_boot_resume_menu_after_slot_refresh(context);
            card_boot_recheck_selected_channel();
            context->progress_dialog_active = 0;
            return;
        }
    }
    context->saved_callback = card_boot_resume_menu_after_slot_refresh;
    card_boot_show_copy_failure_notice(NODE_HEADER(context));
    NODE_HEADER(context)->update_callback = card_boot_restore_saved_selection_callback;
    card_boot_recheck_selected_channel();
    context->progress_dialog_active = 0;
}

#include "modules/dungeon_ovl_1831cd8.h"

void handle_menu_button_input(void *menu) {
    GameWork *input = &g_game_work;
    s32 held_buttons;
    s32 buttons;
    s32 cursor_step = 0;
    s32 repeat_count;
    s32 new_offset;
    s32 old_offset;
    s32 row_count;
    s32 rows_left;

    held_buttons = input->buttons;
    if (held_buttons == 0) {
        return;
    }

    buttons = ((s32)input->unk_010);
    if (buttons & 0x20) {
        SD_Call(0x515);
        ((ovl_1831cd8_818127A8_S_800277A8_1_pre *)menu)[-1].unk_00 = (void *)tick_menu_countdown;
        ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_00 = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_04;
        clear_menu_embedded_state((u8 *)menu - 0x20);
        reset_object_to_default_data(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_44);
        return;
    }

    if (buttons & 0x10) {
        SD_Call(0x503);
        reset_menu_object_state_2(menu);
        forward_stored_object_value(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_44);
        return;
    }

    if (buttons & 0x40) {
        SD_Call(0x503);
        dispatch_menu_state_update((u8 *)menu + 0x38, ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_14,
                      (((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_08 / 72) * 72,
                      ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_28);
        copy_string_to_object_buffer(func_8002553C(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_44),
                      ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_40 +
                      (((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_08 % 72) * 2);
        return;
    }

    if (held_buttons & 0x5000) {
        if (buttons & 0x5000) {
            ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_0C = 0;
            buttons = ((s32)input->unk_010);
            if (buttons & 0x1000) {
                cursor_step = -9;
            } else if (buttons & 0x4000) {
                cursor_step = 9;
            }
        } else {
            repeat_count = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_0C;
            if (repeat_count >= 9) {
                ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_0C = repeat_count - 1;
                buttons = input->buttons;
                if (buttons & 0x1000) {
                    cursor_step = -9;
                } else if (buttons & 0x4000) {
                    cursor_step = 9;
                }
            } else {
                ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_0C = repeat_count + 1;
            }
        }
    }

    if (cursor_step == 0) {
        return;
    }

    SD_Call(0x502);
    new_offset = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_08 + cursor_step;
    row_count = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_3C;
    rows_left = row_count - new_offset / 9;
    if (rows_left <= 0 || row_count < rows_left) {
        return;
    }

    old_offset = new_offset - cursor_step;
    ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_08 = new_offset;
    if (new_offset / 72 != old_offset / 72) {
        clear_menu_state_values(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_88);
        ((ovl_1831cd8_818127A8_S_800277A8_1_pre *)menu)[-1].unk_00 = (void *)run_menu_countdown_callback;
        ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_00 = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_04;
        return;
    }

    position_menu_grid_entries(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_88, new_offset);
}

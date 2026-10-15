#include "modules/dungeon_ovl_1831cd8.h"

void func_800277A8(void *menu) {
    GameWork *input = &gameWork;
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
        ((ovl_1831cd8_818127A8_S_800277A8_1_pre *)menu)[-1].unk_00 = (void *)func_80027E10;
        ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_00 = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_04;
        func_80028620((u8 *)menu - 0x20);
        func_80025598(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_44);
        return;
    }

    if (buttons & 0x10) {
        SD_Call(0x503);
        func_800274A8(menu);
        func_800255AC(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_44);
        return;
    }

    if (buttons & 0x40) {
        SD_Call(0x503);
        func_80027454((u8 *)menu + 0x38, ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_14,
                      (((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_08 / 72) * 72,
                      ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_28);
        func_8002661C(func_8002553C(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_44),
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
        func_80026CD8(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_88);
        ((ovl_1831cd8_818127A8_S_800277A8_1_pre *)menu)[-1].unk_00 = (void *)func_80027E84;
        ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_00 = ((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_04;
        return;
    }

    func_80026D0C(((ovl_1831cd8_818127A8_S_800277A8_1 *)menu)->unk_88, new_offset);
}

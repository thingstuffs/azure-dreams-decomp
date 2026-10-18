#include "modules/dungeon_ovl_1831cd8.h"

void initialize_menu_panel_rows(void *panel, void *widgets) {
    s16 row_y;
    s16 row_x;
    s32 slot_index;
    void **widget_slot;
    ovl_1831cd8_818130FC_S_800280FC_3 *widget_data;

    *((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_00 = &D_80078AB4;
    *((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_04 = &D_80078AD8;
    func_8004CBFC(panel + 0x2C, &D_80079324, ((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_08);
    *((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_0C = 0;
    ((ovl_1831cd8_818130FC_S_800280FC_6 *)(((ovl_1831cd8_818130FC_S_800280FC_4 *)widgets)->unk_10))->unk_00 = 0;
    ((ovl_1831cd8_818130FC_S_800280FC_9 *)(((ovl_1831cd8_818130FC_S_800280FC_6 *)(((ovl_1831cd8_818130FC_S_800280FC_4 *)widgets)->unk_10))->unk_04))->unk_08 = 0x58;
    *((ovl_1831cd8_818130FC_S_800280FC_0 *)widgets)->unk_14 = ((ovl_1831cd8_818130FC_S_800280FC_1 *)panel)->unk_4C + 0x18;
    draw_menu_progress_bar(panel, 0, 1);
    slot_index = 6;
    row_x = 0x58;
    row_y = 0x90;
    widget_slot = widgets + 0x18;
    do {
        ((ovl_1831cd8_818130FC_S_800280FC_2 *)(*widget_slot))->unk_00 = 0;
        ((ovl_1831cd8_818130FC_S_800280FC_7 *)(((ovl_1831cd8_818130FC_S_800280FC_5 *)(*widget_slot))->unk_04))->unk_08 = row_x;
        slot_index += 1;
        widget_data = ((ovl_1831cd8_818130FC_S_800280FC_2 *)(*widget_slot))->unk_04;
        widget_slot = (void **)((s8 *)((void **)((s8 *)widget_slot + 4)));
        widget_data->unk_0A = row_y;
        row_y += 0x10;
    } while (slot_index < 0xE);
    ((ovl_1831cd8_818130FC_S_800280FC_10 *)(((ovl_1831cd8_818130FC_S_800280FC_8 *)(((ovl_1831cd8_818130FC_S_800280FC_4 *)widgets)->unk_38))->unk_04))->unk_08 = 0x4C;
    ((ovl_1831cd8_818130FC_S_800280FC_8 *)(((ovl_1831cd8_818130FC_S_800280FC_4 *)widgets)->unk_38))->unk_00 = 0;
}

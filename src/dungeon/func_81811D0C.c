#include "modules/dungeon_ovl_1831cd8.h"

void position_menu_grid_entries(ovl_1831cd8_81811D0C_S_80026D0C_0 *display, s32 cell_index) {
    s32 row_y;
    s32 x_offset;
    s32 column_x;
    ovl_1831cd8_81811D0C_S_80026D0C_1 *element_node;
    ovl_1831cd8_81811D0C_S_80026D0C_2 *element;

    column_x = ((cell_index % 72) % 9) * 0xB;
    ((ovl_1831cd8_81811D0C_S_80026D0C_7 *)(((ovl_1831cd8_81811D0C_S_80026D0C_3 *)(display->unk_0C))->unk_04))->unk_08 =
        (s16)(column_x - 0x2B);
    row_y = ((cell_index % 72) / 9) * 0x10;
    ((ovl_1831cd8_81811D0C_S_80026D0C_7 *)(((ovl_1831cd8_81811D0C_S_80026D0C_3 *)(display->unk_0C))->unk_04))->unk_0A =
        (s16)(row_y + 0xF);
    element_node = display->unk_10;
    x_offset = ((ovl_1831cd8_81811D0C_S_80026D0C_4 *)(element_node->unk_00))->unk_0A;
    element_node = element_node->unk_04;
    x_offset = (u32)x_offset >> 1;
    x_offset -= 0x29;
    element_node->unk_08 = (s16)(column_x + x_offset);
    element = display->unk_10;
    ((ovl_1831cd8_81811D0C_S_80026D0C_5 *)(element->unk_04))->unk_0A =
        (s16)(row_y + ((((ovl_1831cd8_81811D0C_S_80026D0C_6 *)(element->unk_00))->unk_0B >> 1) + 0xF));
}

#include "modules/dungeon_ovl_1830850.h"

void inventory_handle_menu_actions_and_repeat(ovl_1830850_81810A0C_DungeonArg *menu) {
    ovl_1830850_81810A0C_DungeonState *input = D_80083160;
    s32 selection_step;

    if (input->unk8 != 0 && menu->unk10 != 0) {
        if (input->unk10 & 0x20) {
            SD_Call(0x515);
            set_object_data_pointer(menu->unk14);
            restore_item_text_before_edit(menu);
        } else if (input->unk10 & 0x40) {
            if (func_800258B0(menu) != 0 || inventory_check_type_four_linked_object(menu) != 0) {
                SD_Call(0x506);
            } else {
                if (menu->unk8 == 4) {
                    SD_Call(0x503);
                } else {
                    SD_Call(0x514);
                }
                inventory_dispatch_indexed_handler(menu, menu->unk8);
            }
        } else if (input->unk10 & 0x10) {
            menu->unk8 = 4;
            inventory_set_paired_index_offset(menu->unk54, menu->unk8);
        } else if (input->unk8 & 0x5000) {
            selection_step = 0;
            if (input->unk10 & 0x5000) {
                menu->unk4 = 0;
                if (input->unk10 & 0x1000) {
                    selection_step = -1;
                } else if (input->unk10 & 0x4000) {
                    selection_step = 1;
                }
            } else {
                if (menu->unk4 >= 9) {
                    menu->unk4 = menu->unk4 - 1;
                    if (input->unk8 & 0x1000) {
                        selection_step = -1;
                    } else if (input->unk8 & 0x4000) {
                        selection_step = 1;
                    }
                } else {
                    menu->unk4 = menu->unk4 + 1;
                }
            }
            if (selection_step != 0) {
                SD_Call(0x502);
                menu->unk8 = advance_index_with_single_wrap(selection_step, menu->unk8, 5);
                inventory_set_paired_index_offset(menu->unk54, menu->unk8);
            }
        }
    }

    inventory_select_null_or_default_data(menu);
}

#include "modules/dungeon_ovl_1830850.h"

void func_80025A0C(ovl_1830850_81810A0C_DungeonArg *menu) {
    ovl_1830850_81810A0C_DungeonState *input = D_80083160;
    s32 selection_step;

    if (input->unk8 != 0 && menu->unk10 != 0) {
        if (input->unk10 & 0x20) {
            SD_Call(0x515);
            func_80025514(menu->unk14);
            func_800258B8(menu);
        } else if (input->unk10 & 0x40) {
            if (func_800258B0(menu) != 0 || func_800259CC(menu) != 0) {
                SD_Call(0x506);
            } else {
                if (menu->unk8 == 4) {
                    SD_Call(0x503);
                } else {
                    SD_Call(0x514);
                }
                func_80025850(menu, menu->unk8);
            }
        } else if (input->unk10 & 0x10) {
            menu->unk8 = 4;
            func_80025888(menu->unk54, menu->unk8);
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
                menu->unk8 = func_80049DE8(selection_step, menu->unk8, 5);
                func_80025888(menu->unk54, menu->unk8);
            }
        }
    }

    func_80025964(menu);
}

/* Relink of matched dungeon/func_8028B660; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_spawns.h"

s32 selectFloorItemWithSpecialOverrides(s8 *out_group, s8 *out_index, s32 unused, s32 skip_special) {
    u8 special_selected;
    special_selected = ((u8 *)D_8001F6F0)[0];

    if ((special_selected == 0) && (skip_special == 0) && (*(s32 *)0x80012090 == 0)) {
        if (((s16 *)D_8008146C)[0] == 12) {
            if (((floor_spawns_isolated_8028B660_S_8001E660_0 *)(D_800E3D7C))->unk_FB == 0) {
                *out_group = 12;
                *out_index = 4;
                ((u8 *)D_8001F6F0)[0] = 1;
                return 1;
            }
        } else if (((s16 *)D_8008146C)[0] == 15) {
            if ((func_80033BC0(0x145E) != 0) && (func_80033BC0(0x1460) == 0)
                && ((func_800A697C(0xD, 1) << 0x10) == 0)) {
                *out_group = 0xD;
                *out_index = 1;
                ((u8 *)D_8001F6F0)[0] = 1;
                return 1;
            }
        } else if (((s16 *)D_8008146C)[0] == 28) {
            if ((func_80033BC0(0xFC3) != 0) && (func_80033BC0(0xFAD) == 0) && ((func_800A697C(1, 8) << 0x10) == 0)) {
                *out_group = 1;
                *out_index = 8;
                ((u8 *)D_8001F6F0)[0] = 1;
                return 1;
            }
        } else if (((s16 *)D_8008146C)[0] == 20) {
            if ((func_80033BC0(0xAC) != 0) && (func_80033BC0(0x12C6) == 0) && ((func_800A697C(0xD, 6) << 0x10) == 0)) {
                *out_group = 0xD;
                *out_index = 6;
                ((u8 *)D_8001F6F0)[0] = 1;
                return 1;
            }
        }
        selectWeightedFloorItem(out_group, out_index);
        return 0;
    } else {
        selectWeightedFloorItem(out_group, out_index);
        return 0;
    }
}

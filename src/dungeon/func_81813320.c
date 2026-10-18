#include "modules/dungeon_ovl_1831cd8.h"

void initialize_menu_object_state(s32 object_addr, s32 initial_value) {
    void *state;

    state = object_addr + 0x20;
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_24 = 0;
    ((ovl_1831cd8_81813320_S_80028320_2 *)(((ovl_1831cd8_81813320_S_80028320_1 *)state)->unk_80))->unk_02 = 0;
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_48 = initial_value;
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_18 = 0;
    dispatch_menu_state_update(object_addr + 0x58, ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_24, 0,
        ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_38);
    initialize_menu_mode_one_fields(((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_5C, ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_24);
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_94 = (s32)link_menu_record_nodes(((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_98);
    format_menu_referenced_values(((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_98);
    func_80028648(object_addr);
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_00 = (void *)dispatch_menu_update_callback;
}

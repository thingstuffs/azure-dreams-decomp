#include "modules/dungeon_ovl_1831cd8.h"

void dungeonInitializeMenuObjectState(s32 object_addr, s32 initial_value) {
    void *state;

    state = object_addr + 0x20;
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_24 = 0;
    ((ovl_1831cd8_81813320_S_80028320_2 *)(((ovl_1831cd8_81813320_S_80028320_1 *)state)->unk_80))->unk_02 = 0;
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_48 = initial_value;
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_18 = 0;
    dungeonDispatchMenuStateUpdate(object_addr + 0x58, ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_24, 0,
        ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_38);
    dungeonInitializeMenuModeOneFields(((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_5C, ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_24);
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_94 = (s32)dungeonLinkMenuRecordNodes(((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_98);
    dungeonFormatMenuReferencedValues(((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_98);
    func_80028648(object_addr);
    ((ovl_1831cd8_81813320_S_80028320_0 *)((u8 *)state - 0x10))->unk_00 = (void *)func_80027D7C;
}

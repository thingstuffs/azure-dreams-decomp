#include "modules/dungeon_ovl_1831cd8.h"

void func_800283B4(s32 object_addr) {
    void *object_state;

    object_state = object_addr + 0x20;
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_14 = 1;
    ((ovl_1831cd8_818133B4_S_800283B4_1 *)(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_80))->unk_02 = 0;
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_08 = 0;
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_28 = ((ovl_1831cd8_818133B4_S_800283B4_2 *)(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_48))->unk_1C;
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_38 = ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_18;
    func_80027454(object_addr + 0x58, ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_14, 0,
        ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_28);
    func_80027FF4(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_4C, ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_14);
    ((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_84 = (s32)func_80027FA4(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_88);
    func_80028534(((ovl_1831cd8_818133B4_S_800283B4_0 *)object_state)->unk_88);
    func_80028648(object_addr);
    ((ovl_1831cd8_818133B4_S_800283B4_0_pre *)object_state)[-1].unk_00 = (void *)func_80027D7C;
}

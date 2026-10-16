#include "modules/dungeon_ovl_1831cd8.h"

void dungeonAdvanceMenuValueFade(void *state) {
    s32 nextStep;

    ((ovl_1831cd8_81812F34_S_80027F34_2 *)(((ovl_1831cd8_81812F34_S_80027F34_1 *)state)->unk_80))->unk_02 =
        (s16) (0x400 - ((s32) (((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_10
        << 0xA) / (s32) ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_14));
    nextStep = ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_10 + 1;
    ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_10 = nextStep;
    if (((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_14 < nextStep) {
        ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_10 = 0;
        ((ovl_1831cd8_81812F34_S_80027F34_0 *)((u8 *)state - 0x10))->unk_00 = (void *)func_80027A68;
    }
    dungeonInvokeEnabledMenuCallback(state);
}

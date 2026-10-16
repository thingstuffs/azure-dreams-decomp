#include "modules/dungeon_ovl_1831cd8.h"

void dungeonHandleMenuRecordCheck(void *record) {
    if (advanceTimedTaggedStream(record + 0x2C) != 0) {
        ((ovl_1831cd8_81812A88_S_80027A88_0 *)((u8 *)record - 0x10))->unk_00 = (void *)func_80027A68;
        ((ovl_1831cd8_81812A88_S_80027A88_0 *)((u8 *)record - 0x10))->unk_10 = 0;
    }
    dungeonInvokeEnabledMenuCallback(record);
}

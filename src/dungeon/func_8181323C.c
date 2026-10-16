#include "modules/dungeon_ovl_1831cd8.h"

void dungeonInitializeMenuObjectFromData(void *object, s32 init_value, s32 init_value_2) {
    dungeonInitializeMenuRecordRange(object, init_value, init_value_2);
    dungeonInitializeMenuHeaderRecords(object, object + 0x78, object + 0x50, object + 0x60);
    dungeonInitializeMenuPanelRows(object, ((Rec_func_80027AD0_arg0 *)object)->unk_88);
}

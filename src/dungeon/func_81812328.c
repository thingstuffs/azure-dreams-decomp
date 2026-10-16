#include "modules/dungeon_ovl_1831cd8.h"

void *dungeonRefreshMenuRecordResource(Rec_func_80027328_arg0 *record, M2C_UNK resource_arg) {
    func_8004B1A4(record->unk_08);
    record->unk_04 = func_80025080(record->unk_00);
    record->unk_08 = dungeonConfigureMenuResource(record->unk_00, resource_arg);
    return record;
}

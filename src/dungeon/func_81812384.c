#include "modules/dungeon_ovl_1831cd8.h"

void *dungeonRebuildMenuResource(Rec_func_80027328_arg0 *record, M2C_UNK resource_arg) {
    s32 resource_value;

    func_8004B1A4(record->unk_08);
    resource_value = dungeonCountMenuEntryMatches(record->unk_00);
    record->unk_04 = resource_value;
    record->unk_08 = dungeonPackSelectedMenuEntries(record->unk_00, resource_arg, resource_value);
    return record;
}

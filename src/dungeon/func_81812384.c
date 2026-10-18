#include "modules/dungeon_ovl_1831cd8.h"

void *rebuild_menu_resource(Rec_func_80027328_arg0 *record, s32 resource_arg) {
    s32 resource_value;

    func_8004B1A4(record->unk_08);
    resource_value = count_menu_entry_matches(record->unk_00);
    record->unk_04 = resource_value;
    record->unk_08 = pack_selected_menu_entries(record->unk_00, resource_arg, resource_value);
    return record;
}

#include "modules/dungeon_ovl_1831cd8.h"

void *refresh_menu_record_resource(Rec_func_80027328_arg0 *record, M2C_UNK resource_arg) {
    func_8004B1A4(record->unk_08);
    record->unk_04 = get_half_byte_length(record->unk_00);
    record->unk_08 = configure_menu_resource(record->unk_00, resource_arg);
    return record;
}

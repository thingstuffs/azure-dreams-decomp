#include "modules/dungeon_ovl_1831cd8.h"

void initialize_menu_object_from_data(void *object, s32 init_value, s32 init_value_2) {
    initialize_menu_record_range(object, init_value, init_value_2);
    initialize_menu_header_records(object, object + 0x78, object + 0x50, object + 0x60);
    initialize_menu_panel_rows(object, ((Rec_func_80027AD0_arg0 *)object)->unk_88);
}

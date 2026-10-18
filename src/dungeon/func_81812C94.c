#include "modules/dungeon_ovl_1831cd8.h"

void update_menu_object_data(void *object) {
    store_scaled_menu_ratio(((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_88, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_00, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_04);
    draw_menu_progress_bar(object, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_00, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_04);
    set_menu_object_scale_fields(((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_88, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_00, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_04);
    refresh_menu_entry_resources(((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_88, ((ovl_1831cd8_81812C94_S_80027C94_0 *)object)->unk_40);
    advance_timed_tagged_stream(object + 0x2C);
}

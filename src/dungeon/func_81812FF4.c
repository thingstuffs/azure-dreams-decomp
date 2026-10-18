#include "modules/dungeon_ovl_1831cd8.h"

void *initialize_menu_mode_one_fields(ovl_1831cd8_81812FF4_S_80027FF4_0 *object, s32 mode) {
    copy_menu_record_template(object);
    if (mode == 1) {
        object->unk_02 = -0x31;
        object->unk_0E = -0x31;
        object->unk_0A = 0x63;
        object->unk_16 = 0x63;
    }
    return object;
}

#include "modules/dungeon_ovl_1830850.h"

void inventory_initialize_object_from_embedded_data(void *object, s32 init_value, s32 init_value_2, s32 init_value_3) {
    initialize_text_editor_context(object, init_value, init_value_2, init_value_3);
    inventory_initialize_owner_patch_and_state(object, object + 0x44, object + 0x1C, object + 0x2C);
    inventory_initialize_owner_pointers_and_offsets(object, ((Rec_func_80025850_arg0 *)object)->unk_54);
}

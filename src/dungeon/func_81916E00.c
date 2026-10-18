#include "modules/dungeon_ovl_1936800.h"

void *create_an_default_rendering_settings_copies_initial_data(s32 *owner_data, Row_81916E00_Copy24 *initial_data) {
    s32 owner_value;
    Row_81916E00_S_80024600_1 *render_state;
    Row_81916E00_S_80024600_0 *object;
    Row_81916E00_Copy24 *object_data;

    object = func_8003FD64(0x212, (s8 *) owner_data - 0x20);
    if (object != NULL) {
        object->unk_10 = &D_8002457C;
        owner_value = *owner_data;
        render_state = object->unk_0C;
        object->unk_24 = 0;
        object->unk_20 = owner_value;
        render_state->unk_0C = 0x808080;
        render_state->unk_12 = 0x7DCF;
        render_state->unk_14 = (u16) (render_state->unk_14 | 0xC);
        render_state->unk_10 = (u16) (render_state->unk_10 | 0x60);
        render_state->unk_14 = (u16) (render_state->unk_14 | 0x100);
        func_8003DB94(render_state, &D_800DEC50, 0);
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        func_8004491C(object, func_80045340);
        object_data = object->unk_08;
        *object_data = *initial_data;
        return object;
    } else {
        return NULL;
    }
}

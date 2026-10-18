#include "modules/dungeon_ovl_1936800.h"

void *create_an_initializes_visual_state_copies_initial_data(s32 object_id, void *initial_data, Row_81916AEC_S_800242EC_2 *source)
{
    Row_81916AEC_S_800242EC_3 *visual;
    void *object;
    Row_81916AEC_S_800242EC_1 *state;
    Row_81916AEC_Copy6 *object_data;
    void *result;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = (u8 *)object + 0x20;
        ((Row_81916AEC_S_800242EC_0 *)object)->unk_10 = &D_800241E4;
        ((Row_81916AEC_S_800242EC_0 *)object)->unk_20 = object_id;
        state->unk_04 = 0;
        state->unk_06 = 8;
        state->unk_08 = 8;
        state->unk_0A = source->unk_2A;
        visual = ((Row_81916AEC_S_800242EC_0 *)object)->unk_0C;
        visual->unk_0D = 0x30;
        visual->unk_0C = 0x30;
        visual->unk_0E = 0xC0;
        visual->unk_12 = 0x7DCF;
        visual->unk_14 |= 0xC;
        visual->unk_10 |= 0x20;
        visual->unk_14 |= 0x100;
        func_8003DB94(visual, &D_800DEC70, 0);
        visual->unk_1E = 0x1000;
        visual->unk_1C = 0x1000;
        func_8004491C(object, func_80045340);
        object_data = ((Row_81916AEC_S_800242EC_0 *)object)->unk_08;
        result = object;
        *object_data = *(Row_81916AEC_Copy6 *)initial_data;
        return object;
    }
    return NULL;
}

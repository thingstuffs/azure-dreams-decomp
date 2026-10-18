#include "modules/dungeon_ovl_18c4828.h"

void *create_randomized_grayscale_effect(s32 context_value, Row_818A4A64_S_818A4A64_2 *initial_position) {
    Row_818A4A64_S_818A4A64_1 *render_state;
    Row_818A4A64_S_818A4A64_0 *object;
    Row_818A4A64_S_818A4A64_3 *position;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        render_state = object->unk_0C;
        object->unk_10 = (M2C_UNK *) func_80024230;
        object->unk_20 = context_value;
        render_state->unk_0E = 0;
        render_state->unk_0D = 0;
        render_state->unk_0C = 0;
        func_8003DB94(render_state, D_800DEAE0, 0);
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_14 |= 0xC;
        func_8004491C(object, (s32) func_80045340);
        position = object->unk_08;
        position->unk_02 = initial_position->unk_02;
        position->unk_06 = initial_position->unk_06;
        position->unk_0A = initial_position->unk_0A;
        return object;
    }
    return NULL;
}

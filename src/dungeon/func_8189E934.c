#include "modules/dungeon_ovl_7e765800.h"

s32 allocate_display_object_and_copy_state(s32 stored_value, void *input, s16 stored_tag) {
    s32 random_or_w2;
    s32 rounded_random;
    void *object;
    Row_8189E934_Tail *state;
    Row_8189E934_S_80024134_1 *display;
    void *input_copy;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = (Row_8189E934_Tail *)((s8 *)object + 0x20);
        ((Row_8189E934_S_80024134_0 *)object)->unk_10 = D_80024020;
        state->value = stored_value;
        ((Row_8189E934_S_80024134_0 *)object)->unk_20 = 0;
        state->tag = stored_tag;
        display = ((Row_8189E934_S_80024134_0 *)object)->unk_0C;
        display->unk_0E = 0x80;
        display->unk_0D = 0x80;
        display->unk_0C = 0x80;
        display->unk_08 = D_80024C78;
        display->unk_12 = 0x7E02;
        display->unk_14 = (u16) (display->unk_14 | 0x100);
        rounded_random = rand();
        random_or_w2 = rounded_random;
        display->unk_1A = (s16) (random_or_w2 % 4096);
        display->unk_1E = 0x800;
        display->unk_1C = 0x800;
        func_8004491C(object, func_80045340);
        input_copy = ((Row_8189E934_S_80024134_0 *)object)->unk_08;
        *(Row_8189E934_Input6 *)input_copy = *(Row_8189E934_Input6 *)input;
        random_or_w2 = *(s32 *)((s8 *)input_copy + 8);
        state->copy = random_or_w2;
        return (s32)object;
    }
    return 0;
}

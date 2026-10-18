#include "modules/dungeon_ovl_193c848.h"

void *create_randomized_source_effect(Row_8191C938_S_8191C938_3 *source)
{
    s32 random_value;
    Row_8191C938_CopyBlock *object_block;
    Row_8191C938_S_8191C938_1 *state;
    Row_8191C938_S_8191C938_2 *render_data;
    void *object;
    Row_8191C938_CopyBlock *source_block;
    void *result;
    register u16 word_override;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = object + 0x20;
        ((Row_8191C938_S_8191C938_0 *)object)->unk_10 = D_80024048;
        ((Row_8191C938_S_8191C938_0 *)object)->unk_20 = source;
        state->unk_04 = 0;
        state->unk_06 = 6;
        random_value = rand();
        state->unk_08 = random_value % 0x1000;
        state->unk_0A = 0x10;
        render_data = ((Row_8191C938_S_8191C938_0 *)object)->unk_0C;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        render_data->unk_0E = 0;
        render_data->unk_12 = 0x7DCF;
        render_data->unk_14 |= 0xC;
        render_data->unk_10 |= 0x20;
        render_data->unk_14 |= 0x100;
        func_8003DB94(render_data, D_800DED70, 0);
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        func_8004491C(object, func_80045340);
        object_block = ((Row_8191C938_S_8191C938_0 *)object)->unk_08;
        source_block = source->unk_20;
        *object_block = *source_block;
        word_override = source->unk_16;
        result = object;
        ((Row_8191C938_S_8191C938_4 *)object_block)->unk_0A = word_override;
        return result;
    }
    result = NULL;
    return result;
}

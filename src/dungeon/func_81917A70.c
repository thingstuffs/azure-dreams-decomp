#include "modules/dungeon_ovl_1936800.h"

s32 func_80025270(void *object, Row_81917A70_Copy24 *src_transform, s16 effect_index) {
    s32 first_word;
    s32 second_word;
    s32 random_value;
    s32 adjusted_random;
    Row_81917A70_S_80025270_1 *state;
    Row_81917A70_Copy24 *transform;
    void *effect;
    s16 saved_index;
    effect = func_8003FD64(0x212, (u8 *)object - 0x20);
    if (effect != NULL) {
        saved_index = effect_index;
        state = effect + 0x20;
        ((Row_81917A70_S_80025270_0 *)effect)->unk_10 = &D_80025094;
        ((Row_81917A70_S_80025270_0 *)effect)->unk_20 = (s32)object;
        state->unk_08 = (s16) (saved_index * 7);
        state->unk_04 = 0;
        state->unk_06 = 0;
        state->unk_0A = 0;
        state->unk_0C = (s16) (saved_index * 0x600);
        state->unk_20 = src_transform->wordC;
        state->unk_24 = src_transform->word10;
        state->unk_28 = src_transform->word14;
        object = ((Row_81917A70_S_80025270_0 *)effect)->unk_0C;
        ((Rec_D_80082E80 *)object)->unk_0C.at02_s8.v = 0x20;
        ((Rec_D_80082E80 *)object)->unk_0C.at01_s8.v = 0x20;
        ((Rec_D_80082E80 *)object)->unk_0C.at00_s8.v = 0x20;
        ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0x7DCF;
        ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)object)->unk_14.at00_u16.v | 0xC);
        ((Rec_D_80082E80 *)object)->unk_10.as_u16 = (u16) (((Rec_D_80082E80 *)object)->unk_10.as_u16 | 0x20);
        ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)object)->unk_14.at00_u16.v | 0x100);
        func_8003DB94(object, &D_800DEB70, 0);
        adjusted_random = rand();
        random_value = adjusted_random;
        if (random_value < 0) {
            adjusted_random = random_value + 0xFFF;
        }
        ((Rec_D_80082E80 *)object)->unk_1A.as_s16 = (s16) (random_value % 4096);
        ((Rec_D_80082E80 *)object)->unk_1C.at02_s16.v = 0x400;
        ((Rec_D_80082E80 *)object)->unk_1C.at00_s16.v = 0x400;
        func_8004491C(effect, func_80045340);
        transform = ((Row_81917A70_S_80025270_0 *)effect)->unk_08;
        *transform = *src_transform;
        first_word = ((Row_81917A70_S_80025270_3 *)transform)->unk_00;
        second_word = ((Row_81917A70_S_80025270_3 *)transform)->unk_04;
        ((Row_81917A70_S_80025270_3 *)transform)->unk_0C = first_word;
        ((Row_81917A70_S_80025270_3 *)transform)->unk_10 = second_word;
        return (s32)effect;
    }
    return 0;
}

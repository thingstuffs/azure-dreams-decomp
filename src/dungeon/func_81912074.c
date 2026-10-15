#include "modules/dungeon_ovl_1930844.h"

void *func_80025874(s32 state_value, ovl_1930844_81912074_Copy24 *source_data, s16 initial_setting) {
    void *obj;
    ovl_1930844_81912074_S_80025874_1 *fields;
    void *object_data;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        ((ovl_1930844_81912074_S_80025874_0 *)obj)->unk_10 = (void *)func_800253F4;
        fields = obj + 0x20;
        ((ovl_1930844_81912074_S_80025874_0 *)obj)->unk_20 = state_value;
        fields->unk_08 = 8;
        fields->unk_10 = 2;
        fields->unk_0E = 0x48;
        fields->unk_12 = 1;
        fields->unk_04 = 0;
        fields->unk_06 = 0;
        fields->unk_0A = 0;
        fields->unk_0C = 0;
        fields->unk_40 = 0xC0;
        fields->unk_42 = 0;
        fields->unk_41 = 0;
        fields->unk_14 = initial_setting;
        object_data = ((ovl_1930844_81912074_S_80025874_0 *)obj)->unk_08;
        *(ovl_1930844_81912074_Copy24 *)object_data = *source_data;
        return obj;
    }
    return 0;
}

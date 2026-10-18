#include "modules/dungeon_ovl_1829800.h"

void *allocate_sprite_data_object(s32 user_data) {
    S_80025170_1 *sprite;
    S_80025170_0 *object;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        sprite = object->unk_0C;
        object->unk_10 = (void *)func_80025014;
        func_8003DB94(sprite, &D_80079444, 0);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0C = 0x2C808080;
        sprite->unk_10 = 0x20;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        object->unk_20 = user_data;
    }
    return object;
}

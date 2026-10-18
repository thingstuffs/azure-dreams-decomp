#include "modules/dungeon_ovl_18b8824.h"

ovl_18b8824_81898DCC_Object *create_sprite_effect_with_data(s32 field_value, s32 *initial_data) {
    ovl_18b8824_81898DCC_Object *obj;
    u8 *sprite;
    s32 *data;

    obj = (ovl_18b8824_81898DCC_Object *)func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = (void *)mark_owner_on_target_completion;
        sprite = obj->sprite;
        obj->field20 = field_value;
        sprite[0xE] = 0x80;
        sprite[0xD] = 0x80;
        sprite[0xC] = 0x80;
        *(s16 *)(sprite + 0x1E) = 0x1400;
        *(s16 *)(sprite + 0x1C) = 0x1400;
        func_8003DB94(sprite, D_80024FC4, 0);
        func_8004491C(obj, func_80045340);

        data = obj->data;
        data[0] = initial_data[0];
        data[1] = initial_data[1];
        data[2] = initial_data[2] + 0xA00000;
        data[3] = initial_data[3];
        data[4] = initial_data[4];
        data[5] = initial_data[5];
        return obj;
    }

    return 0;
}

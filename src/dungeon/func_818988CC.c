#include "modules/dungeon_ovl_18b8824.h"

void *create_a_sprite_random_rotation_copies_initial_data(void *context, ovl_18b8824_818988CC_Copy24 *copy_src, s16 initial_value)
{
    ovl_18b8824_818988CC_Object *obj;
    ovl_18b8824_818988CC_S_800240CC_0 *fields;
    ovl_18b8824_818988CC_Sprite *sprite;
    ovl_18b8824_818988CC_Copy24 *dst;
    s32 random_value;

    obj = (ovl_18b8824_818988CC_Object *)func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = (void *)interpolate_view_parameters;
        fields = (u8 *)obj + 0x20;
        fields->unk_0C = context;
        fields->unk_10 = 0;
        fields->unk_12 = initial_value;

        sprite = obj->sprite;
        sprite->color[2] = 0x80;
        sprite->color[1] = 0x80;
        sprite->color[0] = 0x80;
        sprite->callback = D_80024E88;
        random_value = rand();
        sprite->rotation = random_value % 0x1000;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;

        func_8004491C(obj, func_80045340);
        dst = obj->dst;
        *dst = *copy_src;
        return obj;
    }
    return 0;
}

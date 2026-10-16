#include "shared/object_node.h"
#include "modules/dungeon_ovl_18b2800.h"
#include "common.h"
#include "shared/slus_callbacks.h"

   /* fields in dungeonCreateRandomlyRotatedSpriteObject */








extern s32 rand(void);

extern u8 D_80025308[];

/* Create an object with a randomly rotated sprite and initialize its copied data. */
void *dungeonCreateRandomlyRotatedSpriteObject(void *context, B22_818928F8_Copy24 *src_data, s16 state_value)
{
    B22_818928F8_Object *obj;
    B22_818928F8_S_818928F8_0 *state;
    B22_818928F8_Sprite *sprite;
    B22_818928F8_Copy24 *dst_data;
    s32 random_rotation;
    B22_818928F8_Object *sprite_obj;

    obj = (B22_818928F8_Object *)func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = func_80024028;
        state = (u8 *)obj + 0x20;
        state->unk_0C = context;
        state->unk_10 = 0;
        state->unk_12 = state_value;

        sprite = obj->sprite;
        sprite->color[2] = 0x80;
        sprite->color[1] = 0x80;
        sprite->color[0] = 0x80;
        sprite->callback = D_80025308;
        random_rotation = rand();
        sprite_obj = obj;
        sprite->rotation = random_rotation % 0x1000;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;

        func_8004491C(sprite_obj, func_80045340);
        dst_data = obj->dst;
        *dst_data = *src_data;
        dst_data->word[5] = (s32)0xFFFF0000;
        return obj;
    }
    return 0;
}

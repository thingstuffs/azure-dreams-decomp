#include "modules/dungeon_ovl_188898c.h"

void delay_and_fade_particle(s32 value, void *source_data) {
    ovl_188898c_81868FDC_Object *obj;
    ovl_188898c_81868FDC_Sprite *sprite;
    u16 *dst;
    u16 *src;

    obj = (ovl_188898c_81868FDC_Object *)func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = (void *)shrink_and_brighten_effect;
        sprite = obj->sprite;
        obj->value = value;
        sprite->b = 0x80;
        sprite->g = 0x80;
        sprite->r = 0x80;
        func_8003DB94(sprite, D_80025368, 0);
        sprite->scale_y = 0x4000;
        sprite->scale_x = 0x4000;
        sprite->angle = 0x7E0B;
        sprite->flags10 |= 0x60;
        sprite->flags14 |= 0x10C;
        func_8004491C(obj, func_80045340);
        dst = obj->dst;
        src = source_data;
        dst[1] = src[1];
        dst[3] = src[3];
        dst[5] = src[5];
    }
}

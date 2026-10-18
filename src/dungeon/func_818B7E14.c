#include "shared/object_node.h"
#include "modules/dungeon_ovl_18d6800.h"
#include "common.h"







extern s32 rand(void);


/* Spawn a 0x212 effect object owned by `owner`, give it a random 12-bit spin and copy the source transform into it. */
s32 spawn_owned_random_spin_effect(void *owner, B28_818B7E14_DungeonSource *source)
{
    s32 random;
    s32 adjusted;
    B28_818B7E14_DungeonObject *obj;
    B28_818B7E14_DungeonRenderData *render;
    u8 *sub;
    B28_818B7E14_DungeonSource *dst;
    s32 copy0;
    s32 copy0_2;
    s32 copy1;
    s32 copy1_2;
    s32 copy2;
    s32 copy3;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        sub = (u8 *)obj + 0x20;
        obj->update = func_8002553C;
        obj->owner = owner;
        *(s16 *)(sub + 0x10) = 0;
        *(u16 *)(sub + 0x14) = *(u16 *)((u8 *)owner + 0x12);
        render = obj->render;
        render->color_b = 0x80;
        render->color_g = 0x80;
        render->color_r = 0x80;
        render->f12 = 0x7E00;
        render->f14 |= 0x100;
        func_8003DB94(render, D_80025EE4, 0);
        random = rand();
        adjusted = random;
        render->f1A = (random % 4096);
        render->f1E = 0x400;
        render->f1C = 0x400;
        func_8004491C(obj, func_80045C34);
        dst = (B28_818B7E14_DungeonSource *)obj->data;

        *dst = *source;
        return obj;
    }
    return 0;
}

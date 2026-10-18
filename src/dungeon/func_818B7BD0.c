#include "shared/object_node.h"
#include "modules/dungeon_ovl_18d6800.h"
#include "common.h"
#include "m2c_compat.h"

   /* obj in spawn_owner_random_variant_effect */

   /* render in spawn_owner_random_variant_effect */

   /* owner in spawn_owner_random_variant_effect */

   /* transform in spawn_owner_random_variant_effect */

   /* dst in spawn_owner_random_variant_effect */




#define M2C_HIGH_WORD(product) ((s32) ((u64) (product).value >> 32))


/* Spawn a 0x212 effect object for the owner with a random variant and spin, and copy the transform into it. */
s32 spawn_owner_random_variant_effect(B28_818B7BD0_S_818B7BD0_2 *owner, B28_818B7BD0_S_818B7BD0_3 *transform) {
    s32 roll;
    s32 random;
    s32 adjusted;
    s32 result;
    void *model;
    void *update_handler;
    B28_818B7BD0_S_818B7BD0_1 *render;
    B28_818B7BD0_S_818B7BD0_1 *part;
    void *obj;
    B28_818B7BD0_S_818B7BD0_4 *dst;

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        update_handler = update_spark_effect;
        part = obj + 0x20;
        ((B28_818B7BD0_S_818B7BD0_0 *)obj)->unk_10 = update_handler;
        ((B28_818B7BD0_S_818B7BD0_0 *)obj)->unk_20 = owner;
        part->unk_0E.s16 = 0;
        part->unk_10 = 0;
        roll = func_80069EF8();
        model = &D_80025EE4;
        part->unk_12 = (s16)(roll % 7);
        part->unk_14 = (u16) owner->unk_12;
        part->unk_18.at00.v = (s32) owner->unk_18;
        render = ((B28_818B7BD0_S_818B7BD0_0 *)obj)->unk_0C;
        render->unk_0E.u8 = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        render->unk_12 = 0x7E00;
        render->unk_14 = (u16) (render->unk_14 | 0x100);
        func_8003DB94(render, model, 0);
        adjusted = func_80069EF8();
        random = adjusted;
        if (random < 0) {
            adjusted = random + 0xFFF;
        }
        render->unk_18.at02.v = (s16) (random % 4096);
        render->unk_1E = 0x400;
        render->unk_1C = 0x400;
        func_8004491C(obj, func_80045C34);
        dst = ((B28_818B7BD0_S_818B7BD0_0 *)obj)->unk_08;
        result = (s32) obj;
        *dst = *(B28_818B7BD0_S_818B7BD0_4 *)transform;
        return result;
    }
    return 0;
}

/* Relink of matched dungeon/func_80A4B678; every changed retail word is a paired relocation. */
#define dungeonCreateSixteenSegmentRing func_80150E78
#define dungeonUpdateFadingFourStripEffect D_80150934
#include "modules/dungeon_resource06_slot0.h"
extern s32 func_800644B8(s32);

void func_80150E78(R06_80174E78_Source *source, R06_80174E78_Vec3i *center, void *unused_context)
{
    s16 segment_index;
    void (*update_callback)(void);
    s32 base_level;

    segment_index = 0;
    update_callback = dungeonUpdateFadingFourStripEffect;
    base_level = 32;
    for (; segment_index < 16; segment_index++) {
        R06_80174E78_Entity *entity;
        R06_80174E78_Sub *sub;
        R06_80174E78_Vec3i *position;
        R06_80174E78_Prim *prim;
        s32 angle;
        s32 next_angle;
        s16 radial_offset;
        u16 prim_flags;
        u16 *prim_flags_ptr;
        R06_80174E78_Entity *setup_entity;
        s32 initial_count;
        s32 unit_scale;
        s32 trig_angle;
        s32 trig_value;

        entity = (R06_80174E78_Entity *)func_8003FC64(18);
        if (entity == 0) {
            continue;
        }

        sub = &entity->sub;
        initial_count = 50;
        setup_entity = entity;
        sub->field_1A = initial_count;
        sub->field_1C = source->field_96;
        entity->callback = update_callback;
        func_8004491C(setup_entity, func_80045340);

        prim = entity->prim;
        prim_flags_ptr = &prim->field_14;
        prim_flags = *(u16 *)prim_flags_ptr;
        prim_flags |= 0xC;
        *prim_flags_ptr = prim_flags;
        prim->field_10 = base_level;
        prim_flags |= 0x80;
        *prim_flags_ptr = prim_flags;

        position = entity->vec;
        position->x = center->x;
        next_angle = (segment_index + 1) << 8;
        position->y = center->y;
        position->z = center->z;

        sub->field_6E = -64;
        sub->field_68 = -64;
        sub->field_7A = 0;
        sub->field_74 = 0;

        trig_value = func_80064584(next_angle);
        angle = segment_index << 8;
        trig_angle = angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->field_70 = radial_offset;
        sub->field_64 = radial_offset;

        trig_value = func_80064584(trig_angle);
        trig_angle = next_angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->field_76 = radial_offset;
        sub->field_6A = radial_offset;

        trig_value = func_800644B8(trig_angle);
        trig_angle = angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->field_72 = radial_offset;
        sub->field_66 = radial_offset;

        trig_value = func_800644B8(trig_angle);
        radial_offset = (trig_value * 24) >> 12;
        sub->field_78 = radial_offset;
        sub->field_6C = radial_offset;

        prim = entity->prim;
        prim->field_0C = 128;
        unit_scale = 4096;
        prim->field_1E = unit_scale;
        prim->field_1C = unit_scale;
        prim->field_0D = base_level;
        prim->field_0E = base_level;
        sub->field_04 = prim->field_0C;
        sub->field_05 = prim->field_0D;
        sub->field_06 = prim->field_0E;
    }
}

#include "modules/dungeon_resource06_slot0.h"
#include "shared/sprite_frame_state.h"

void create_sixteen_segment_ring(R06_80174E78_Source *source, R06_80174E78_Vec3i *center, void *unused_context)
{
    s16 segment_index;
    void (*update_callback)(void);
    s32 base_level;

    segment_index = 0;
    update_callback = update_fading_four_strip_effect;
    base_level = 32;
    for (; segment_index < 16; segment_index++) {
        R06_80174E78_Entity *entity;
        R06_80174E78_Sub *sub;
        R06_80174E78_Vec3i *position;
        SpriteFrameState *prim;
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
        register_node(setup_entity, project_sprite_chain);

        prim = entity->prim;
        prim_flags_ptr = &prim->flags;
        prim_flags = *(u16 *)prim_flags_ptr;
        prim_flags |= 0xC;
        *prim_flags_ptr = prim_flags;
        prim->tpage_abr = base_level;
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
        prim->color.c.r = 128;
        unit_scale = 4096;
        prim->scale_y = unit_scale;
        prim->scale_x = unit_scale;
        prim->color.c.g = base_level;
        prim->color.c.b = base_level;
        sub->field_04 = prim->color.c.r;
        sub->field_05 = prim->color.c.g;
        sub->field_06 = prim->color.c.b;
    }
}

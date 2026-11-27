#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "dungeon/monster/nyuel.h"
#include "sdk/libgte.h"




typedef struct {
    u8 pad_00[4];
    u8 red;
    u8 green;
    u8 blue;
    u8 pad_07[0x13];
    s16 lifetime;
    u16 field_1C;
    u8 pad_1E[0x46];
    s16 vertex0_x;
    s16 vertex0_y;
    s16 vertex0_z;
    s16 vertex1_x;
    s16 vertex1_y;
    s16 vertex1_z;
    s16 vertex2_x;
    s16 vertex2_y;
    s16 vertex2_z;
    s16 vertex3_x;
    s16 vertex3_y;
    s16 vertex3_z;
} Sub;

typedef struct {
    ObjectNodeHeader header;
    Sub sub;
} Entity;

/* Creates a 16-segment cylindrical effect at the supplied position. */
void create_cylindrical_effect(ActorRecord *source, ObjectPosition *origin)
{
    s16 segment;
    void (*callback)(struct EffectState *, s32 *, SpriteFrameState *);
    s32 base_color;

    segment = 0;
    callback = fade_effect_and_spawn_textured_objects;
    base_color = 32;
    for (; segment < 16; segment++) {
        Entity *entity;
        Sub *sub;
        ObjectPosition *position;
        SpriteFrameState *prim;
        s32 angle;
        s32 next_angle;
        s16 radial_offset;
        Entity *init_entity;
        s32 lifetime;
        s32 unit_scale;
        u8 color_copy;
        s32 trig_angle;
        s32 trig_value;

        entity = allocate_flagged_object_node(18);
        if (entity == 0) {
            continue;
        }

        sub = &entity->sub;
        lifetime = 50;
        init_entity = entity;
        sub->lifetime = lifetime;
        sub->field_1C = source->action_timer;
        entity->header.update_callback = callback;
        register_node(&init_entity->header, project_sprite_chain);

        prim = entity->header.sprite;
        prim->flags |= 0xC;
        prim->tpage_abr = base_color;
        prim->flags |= 0x80;

        position = entity->header.position;
        position->x.v = origin->x.v;
        next_angle = (segment + 1) << 8;
        position->y.v = origin->y.v;
        position->z.v = origin->z.v;

        sub->vertex1_z = -64;
        sub->vertex0_z = -64;
        sub->vertex3_z = 0;
        sub->vertex2_z = 0;

        trig_value = rcos(next_angle);
        angle = segment << 8;
        trig_angle = angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->vertex2_x = radial_offset;
        sub->vertex0_x = radial_offset;

        trig_value = rcos(trig_angle);
        trig_angle = next_angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->vertex3_x = radial_offset;
        sub->vertex1_x = radial_offset;

        trig_value = rsin(trig_angle);
        trig_angle = angle;
        radial_offset = (trig_value * 24) >> 12;
        sub->vertex2_y = radial_offset;
        sub->vertex0_y = radial_offset;

        trig_value = rsin(trig_angle);
        radial_offset = (trig_value * 24) >> 12;
        sub->vertex3_y = radial_offset;
        sub->vertex1_y = radial_offset;

        prim = entity->header.sprite;
        prim->color.c.r = base_color;
        color_copy = base_color;
        unit_scale = 4096;
        prim->scale_y = unit_scale;
        prim->scale_x = unit_scale;
        prim->color.c.g = 128;
        prim->color.c.b = base_color;
        sub->red = prim->color.c.r;
        sub->green = prim->color.c.g;
        sub->blue = prim->color.c.b;
    }
}

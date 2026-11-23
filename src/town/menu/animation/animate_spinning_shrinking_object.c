#include "common.h"
#include "engine/graphics/sprite_scratch.h"
#include "town/menu/motion.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "town/menu.h"
#include "town/menu/animation.h"


typedef union TownReciprocal {
    u16 bits;
    s16 signed_value;
} TownReciprocal;

/* Spin and shrink the object, update both transforms, and mark completion at zero extent. */
s32 animate_spinning_shrinking_object(struct DoorTransitionEffect *object, const struct ObjectPosition *point, struct SpriteFrameState *unused_sprite)
{
    SpriteLinkedScratch *scratch = LINKED_SPRITE_SCRATCH;
    VECTOR *translation;
    SVECTOR *rotation;
    VECTOR *scale;
    MATRIX *first_matrix;
    MATRIX *second_matrix;
    s32 animation_time;
    s32 wave_value;
    u16 spin_angle;

    spin_angle = object->angle_y;
    spin_angle += 0x16;
    object->angle_y = spin_angle;
    {
        s32 next_timer;

        next_timer = object->timer + 5;
        object->timer = next_timer;
        object->intensity += 5;
        if (next_timer >= 0xFF)
            object->timer = 0xFF;
    }

    animation_time = object->timer;
    if (animation_time < 0xC1)
        wave_value = rsin(animation_time * 5);
    else
        wave_value = rsin((animation_time * 0x10) - 0x400);
    if (wave_value < 0) {
        wave_value += 0xF;
        object->intensity = wave_value >> 4;
    } else {
        object->intensity = wave_value >> 4;
    }
    if (object->intensity >= 0xFF)
        object->intensity = 0xFF;

    object->extent -= 6;
    if (object->extent < 0)
        object->extent = 0;

    translation = &scratch->translation;
    PushMatrix();
    scratch->translation.vx = point->x.w.i;
    scratch->translation.vy = point->y.w.i;
    scratch->translation.vz = point->z.w.i - (object->half_height / 2);
    scratch->input.vx = object->extent;
    scratch->input.vy = object->extent;
    scratch->input.vz = object->extent;

    scratch->work_vector.vx = object->angle_x;
    scratch->work_vector.vy = object->angle_y;
    scratch->work_vector.vz = object->angle_z;
    first_matrix = &object->matrices[0];
    TransMatrix(first_matrix, translation);

    rotation = &scratch->work_vector;
    RotMatrix(rotation, first_matrix);
    scale = &scratch->input;
    ScaleMatrix(first_matrix, scale);

    scratch->work_vector.vx = -object->angle_x;
    scratch->work_vector.vy = -object->angle_y;
    scratch->work_vector.vz = -object->angle_z;
    second_matrix = &object->matrices[1];
    TransMatrix(second_matrix, translation);
    RotMatrix(rotation, second_matrix);
    ScaleMatrix(second_matrix, scale);
    PopMatrix();
    draw_random_tinted_quad_pair(object);

    if (object->extent == 0) {
        object->finished = 1;
        return 1;
    }
    return 0;
}

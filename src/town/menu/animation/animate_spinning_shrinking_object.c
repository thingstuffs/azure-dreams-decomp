#include "common.h"
#include "shared/position_views.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "town/menu.h"
#include "town/menu/animation.h"

typedef struct TownScratch {
    u8 pad_00[0x2C];
    SVECTOR rotation; /* RotMatrix angles: the object angles, then their negation */
    VECTOR scale; /* ScaleMatrix scale: the object extent on every axis */
    VECTOR translation; /* TransMatrix translation: the anchor point */
} TownScratch;

typedef s16 TownExtent;

typedef union TownReciprocal {
    u16 bits;
    s16 signed_value;
} TownReciprocal;

typedef struct TownObject {
    u16 angle_x;
    u16 angle_y;
    u16 angle_z;
    u8 pad_06[2];
    TownExtent extent;
    s16 finished;
    s32 timer;
    TownReciprocal reciprocal;
    u8 pad_12[2];
    MATRIX first_matrix;
    MATRIX second_matrix;
    u8 pad_54[0x26];
    s16 half_height;
} TownObject;

/* Spin and shrink the object, update both transforms, and mark completion at zero extent. */
s32 animate_spinning_shrinking_object(TownObject *object, const SignedPositionView *point, s32 unused_arg2)
{
    TownScratch *scratch = (TownScratch *)0x1F800000;
    VECTOR *translation;
    SVECTOR *rotation;
    VECTOR *scale;
    MATRIX *first_matrix;
    MATRIX *second_matrix;
    s32 animation_time;
    s32 wave_value;
    u16 spin_angle;
    u16 reciprocal;
    u16 extent;

    spin_angle = object->angle_y;
    spin_angle += 0x16;
    object->angle_y = spin_angle;
    {
        s32 next_timer;

        next_timer = object->timer + 5;
        object->timer = next_timer;
        reciprocal = object->reciprocal.bits + 5;
        object->reciprocal.bits = reciprocal;
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
        object->reciprocal.bits = wave_value >> 4;
    } else {
        object->reciprocal.bits = wave_value >> 4;
    }
    if (object->reciprocal.signed_value >= 0xFF)
        object->reciprocal.bits = 0xFF;

    extent = (u16)object->extent - 6;
    object->extent = extent;
    if ((s16)extent < 0)
        object->extent = 0;

    translation = &scratch->translation;
    PushMatrix();
    scratch->translation.vx = point->x;
    scratch->translation.vy = point->y;
    scratch->translation.vz = point->z - (object->half_height / 2);
    scratch->scale.vx = object->extent;
    scratch->scale.vy = object->extent;
    scratch->scale.vz = object->extent;

    scratch->rotation.vx = object->angle_x;
    scratch->rotation.vy = object->angle_y;
    scratch->rotation.vz = object->angle_z;
    first_matrix = &object->first_matrix;
    TransMatrix(first_matrix, translation);

    rotation = &scratch->rotation;
    RotMatrix(rotation, first_matrix);
    scale = &scratch->scale;
    ScaleMatrix(first_matrix, scale);

    scratch->rotation.vx = -object->angle_x;
    scratch->rotation.vy = -object->angle_y;
    scratch->rotation.vz = -object->angle_z;
    second_matrix = &object->second_matrix;
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

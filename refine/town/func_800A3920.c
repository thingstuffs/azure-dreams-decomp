#include "common.h"

typedef struct TownMatrix {
    u8 bytes[0x20];
} TownMatrix;

typedef struct TownVec16 {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} TownVec16;

typedef struct TownVec32 {
    s32 x;
    s32 y;
    s32 z;
    s32 pad;
} TownVec32;

typedef struct TownScratch {
    u8 pad_00[0x2C];
    TownVec16 rotation;
    TownVec32 scale;
    TownVec32 translation;
} TownScratch;

typedef union TownExtent {
    u16 bits;
    s16 signed_value;
} TownExtent;

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
    TownMatrix first_matrix;
    TownMatrix second_matrix;
    u8 pad_54[0x26];
    s16 half_height;
} TownObject;

typedef struct TownPoint {
    u8 pad_00[2];
    s16 x;
    u8 pad_04[2];
    s16 y;
    u8 pad_08[2];
    s16 z;
} TownPoint;

extern s32 func_800644B8(s32 angle);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064B90(TownMatrix *matrix, TownVec32 *translation);
extern void func_80065820(TownVec16 *rotation, TownMatrix *matrix);
extern void func_80064BC0(TownMatrix *matrix, TownVec32 *scale);
extern void func_800A1354(TownObject *object);

/* Spin and shrink the object, update both transforms, and mark completion at zero extent. */
s32 func_800A1080(TownObject *object, const TownPoint *point)
{
    TownScratch *scratch = (TownScratch *)0x1F800000;
    TownVec32 *translation;
    TownVec16 *rotation;
    TownVec32 *scale;
    TownMatrix *first_matrix;
    TownMatrix *second_matrix;
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
        wave_value = func_800644B8(animation_time * 5);
    else
        wave_value = func_800644B8((animation_time * 0x10) - 0x400);
    if (wave_value < 0) {
        wave_value += 0xF;
        object->reciprocal.bits = wave_value >> 4;
    } else {
        object->reciprocal.bits = wave_value >> 4;
    }
    if (object->reciprocal.signed_value >= 0xFF)
        object->reciprocal.bits = 0xFF;

    extent = object->extent.bits - 6;
    object->extent.bits = extent;
    if ((s16)extent < 0)
        object->extent.bits = 0;

    translation = &scratch->translation;
    func_800649A0();
    scratch->translation.x = point->x;
    scratch->translation.y = point->y;
    scratch->translation.z = point->z - (object->half_height / 2);
    scratch->scale.x = object->extent.signed_value;
    scratch->scale.y = object->extent.signed_value;
    scratch->scale.z = object->extent.signed_value;

    scratch->rotation.x = object->angle_x;
    scratch->rotation.y = object->angle_y;
    scratch->rotation.z = object->angle_z;
    first_matrix = &object->first_matrix;
    func_80064B90(first_matrix, translation);

    rotation = &scratch->rotation;
    func_80065820(rotation, first_matrix);
    scale = &scratch->scale;
    func_80064BC0(first_matrix, scale);

    scratch->rotation.x = -object->angle_x;
    scratch->rotation.y = -object->angle_y;
    scratch->rotation.z = -object->angle_z;
    second_matrix = &object->second_matrix;
    func_80064B90(second_matrix, translation);
    func_80065820(rotation, second_matrix);
    func_80064BC0(second_matrix, scale);
    func_80064A40();
    func_800A1354(object);

    if (object->extent.signed_value == 0) {
        object->finished = 1;
        return 1;
    }
    return 0;
}

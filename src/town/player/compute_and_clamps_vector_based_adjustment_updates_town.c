#include "common.h"
#include "sdk/libc.h"
#include "town/player.h"

typedef struct TownObj {
    s32 unk0;
    s32 unk4;
    s32 value8;
    s32 valueC;
    s32 value10;
    s32 value14;
} TownObj;

typedef struct TownVec {
    s16 x;
    s16 y;
    s16 divisor;
} TownVec;

extern s8 D_800CFCE9;

/* Computes and clamps a vector-based adjustment, then updates the town object. */
void compute_and_clamps_vector_based_adjustment_updates_town(ObjectPosition *obj, s32 base_value, TownVec **vec_ptr)
{
    TownVec *vec;
    s32 x;
    s32 y;
    s32 initial_base_value;
    s32 abs_x;
    s32 abs_y;
    s32 adjustment;
    s32 clamp_value;

    D_800CFCE9 = 1;
    initial_base_value = base_value << 16;
    obj->z.v = initial_base_value;
    vec = *vec_ptr;
    x = vec->x;
    if ((x == 0 && vec->y == 0) || (base_value = vec->divisor) == 0) {
        obj->velocity_z = 0;
    } else {
        y = vec->y;
        abs_x = x;
        abs_x = abs(abs_x);
        abs_y = y;
        abs_y = abs(abs_y);
        if (abs_y < abs_x) {
            adjustment = (((-obj->velocity_x) << 8) / base_value) * x;
        } else {
            adjustment = (((-obj->velocity_y) << 8) / base_value) * y;
        }
        if (adjustment < 0) {
            adjustment = (adjustment + 0xFF) >> 8;
            obj->velocity_z = adjustment;
        } else {
            adjustment >>= 8;
            obj->velocity_z = adjustment;
        }
        clamp_value = obj->velocity_z;
        if (clamp_value > 0xCC000) {
            obj->velocity_z = 0xCC000;
        } else if (clamp_value < -0xCC000) {
            obj->velocity_z = -0xCC000;
        }
    }
    clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(obj);
}

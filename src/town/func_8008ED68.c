/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 pad;
} S_8008ECC0;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 pad[3];
} S_8008ECC0_Vec;

extern s16 forward_smallest_surface_x_query(S_8008ECC0_Vec *record);

/* Queries a surface X bound at an indexed offset, subtracting that offset's X unless the result is 0x7FFF. */
s16 evaluate_summed_vector_minus_base(S_8008ECC0 *position, S_8008ECC0 *offsets, s32 offset_index)
{
    S_8008ECC0_Vec query_position;
    S_8008ECC0 *offset;
    s16 result;

    offset_index *= sizeof(S_8008ECC0);
    offset = (S_8008ECC0 *)(offset_index + (unsigned long)offsets);
    query_position.x = position->x + offset->x;
    query_position.y = position->y + offset->y;
    query_position.z = position->z + offset->z;
    result = forward_smallest_surface_x_query(&query_position);

    if (result == (s16)0x7FFF) {
        return (u16)0x7FFF;
    }
    return result - offset->x / 0x10000;
}

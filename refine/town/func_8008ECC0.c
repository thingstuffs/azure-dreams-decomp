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

extern s16 func_8008CF80(S_8008ECC0_Vec *arg0);

/* Query the summed position and subtract the selected offset's integer z component. */
s16 func_8008C420(S_8008ECC0 *position, S_8008ECC0 *offsets, s32 offset_index)
{
    S_8008ECC0_Vec query_position;
    S_8008ECC0 *offset;
    s16 result;

    offset_index *= sizeof(S_8008ECC0);
    offset = (S_8008ECC0 *)(offset_index + (unsigned long)offsets);
    query_position.x = position->x + offset->x;
    query_position.y = position->y + offset->y;
    query_position.z = position->z + offset->z;
    result = func_8008CF80(&query_position);

    if (result == (s16)0x8001) {
        return (u16)0x8001;
    }
    return result - offset->z / 0x10000;
}

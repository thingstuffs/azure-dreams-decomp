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

s16 func_8008C420(S_8008ECC0 *arg0, S_8008ECC0 *arg1, s32 arg2)
{
    S_8008ECC0_Vec sp10;
    S_8008ECC0 *entry;
    s16 result;

    arg2 *= sizeof(S_8008ECC0);
    entry = (S_8008ECC0 *)(arg2 + (unsigned long)arg1);
    sp10.x = arg0->x + entry->x;
    sp10.y = arg0->y + entry->y;
    sp10.z = arg0->z + entry->z;
    result = func_8008CF80(&sp10);

    if (result == (s16)0x8001) {
        return (u16)0x8001;
    }
    return result - entry->z / 0x10000;
}

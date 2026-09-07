#include "common.h"

#define NULL 0

typedef struct {
    s16 x0;
    s16 y0;
    s16 pad4;
    s16 pad6;
    s16 x1;
    s16 y1;
} CoordPair;

extern void **D_801007F4;

void **func_8009CDCC(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                     CoordPair *coords)
{
    if (coords != NULL) {
        void **cursor = D_801007F4;

        coords->x0 = (s16)((s32)(arg0 << 16) >> 10);
        coords->y0 = (s16)((s32)(arg1 << 16) >> 10);
        coords->x1 = (s16)((s32)(arg2 << 16) >> 10);
        coords->y1 = (s16)((s32)(arg3 << 16) >> 10);
        *cursor = coords;
        cursor++;
        D_801007F4 = cursor;
        *cursor = NULL;
    }
    return D_801007F4;
}

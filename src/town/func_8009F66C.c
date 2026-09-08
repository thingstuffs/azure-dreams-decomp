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

/* Scale a coordinate pair by 64 and append it to the null-terminated pointer list. */
void **func_8009CDCC(s32 firstX, s32 firstY, s32 secondX, s32 secondY,
                     CoordPair *coords)
{
    if (coords != NULL) {
        void **cursor = D_801007F4;

        coords->x0 = (s16)((s32)(firstX << 16) >> 10);
        coords->y0 = (s16)((s32)(firstY << 16) >> 10);
        coords->x1 = (s16)((s32)(secondX << 16) >> 10);
        coords->y1 = (s16)((s32)(secondY << 16) >> 10);
        *cursor = coords;
        cursor++;
        D_801007F4 = cursor;
        *cursor = NULL;
    }
    return D_801007F4;
}

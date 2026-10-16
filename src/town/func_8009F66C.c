#include "modules/town_town_windows.h"

/* Scale a coordinate pair by 64 and append it to the null-terminated pointer list. */
void **townScaleCoordinatesAndAppendPointers(s32 firstX, s32 firstY, s32 secondX, s32 secondY,
                     func_8009F66C_CoordPair *coords)
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

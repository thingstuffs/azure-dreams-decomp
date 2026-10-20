#include "common.h"

/* File-coordinate identity; placement and storage owner remain unresolved. */
typedef struct { s16 x; s16 y; } DirectionOffset;

const DirectionOffset D_80921000[8] = {
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {0, -1},
    {1, -1},
};

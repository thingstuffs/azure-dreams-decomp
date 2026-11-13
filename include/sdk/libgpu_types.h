#ifndef SDK_LIBGPU_TYPES_H
#define SDK_LIBGPU_TYPES_H

#include "common.h"

/* Psy-Q RECT: a VRAM or screen rectangle (LoadImage, StoreImage, MoveImage, ClearImage, SetDrawArea). */
typedef struct RECT {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} RECT;

/* Psy-Q DR_MODE: the draw-mode packet SetDrawMode fills (a tag word and two GPU command words). */
typedef struct DR_MODE {
    u32 tag;
    u32 code[2];
} DR_MODE;

/* Psy-Q DR_PRIO: the mask-bit packet SetPriority fills (a tag word, the GP0(E6) command word and a zero word). */
typedef struct DR_PRIO {
    u32 tag;
    u32 code[2];
} DR_PRIO;

#endif

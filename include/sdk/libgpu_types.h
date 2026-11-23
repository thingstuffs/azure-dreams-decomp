#ifndef SDK_LIBGPU_TYPES_H
#define SDK_LIBGPU_TYPES_H

#include "common.h"

/* DMA/GPU packet tag: addr is the next packet's low 24-bit address,
 * len is the command-word count in the high byte. The existing bitfield
 * consumers in the layered renderer and text renderer use this layout. */
/* DMA tag embedded in a render packet; builders set its count and link it into the ordering table.
 * It has the containing packet's frame lifetime; changing addr must preserve the high length byte. */
typedef struct GpuLinkTag {
    unsigned int addr : 24; /* next packet address, low 24 bits */
    unsigned int len : 8; /* number of following GPU command words, in 32-bit words */
} GpuLinkTag;


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

/* VRAM move packet emitted by SetDrawMove. */
typedef struct DR_MOVE {
    u32 tag;
    u32 code[5];
} DR_MOVE;

#endif

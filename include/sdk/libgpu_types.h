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

/* Psy-Q DR_ENV: the drawing-environment packet PutDrawEnv sends (a tag word and fifteen command words). */
typedef struct DR_ENV {
    u32 tag;
    u32 code[15];
} DR_ENV;

/* Psy-Q DRAWENV: the drawing environment SetDefDrawEnv fills and PutDrawEnv applies (0x5C bytes). */
typedef struct DRAWENV {
    RECT clip; /* drawing area; SetDrawArea takes it */
    s16 ofs[2]; /* drawing offset */
    RECT tw; /* texture window */
    u16 tpage; /* initial texture page */
    u8 dtd; /* dither flag */
    u8 dfe; /* draw-on-display flag */
    u8 isbg; /* clear the area with the colour below when applied */
    u8 r0, g0, b0; /* background colour */
    DR_ENV dr_env;
} DRAWENV;

/* Psy-Q DISPENV: the display environment SetDefDispEnv fills and PutDispEnv applies (0x14 bytes). */
typedef struct DISPENV {
    RECT disp; /* displayed VRAM area */
    RECT screen; /* output screen position and size */
    u8 isinter; /* interlace flag */
    u8 isrgb24; /* 24-bit colour flag */
    u8 pad0, pad1;
} DISPENV;

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

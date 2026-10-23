#ifndef TOWN_MENU_LINE_EFFECTS_H
#define TOWN_MENU_LINE_EFFECTS_H

#include "common.h"
#include "shared/sprite_frame_state.h"

/* Both line builders write an RGB word followed by unsigned screen halves.
 * SetLineG4 uses four vertices and a trailing termination word (0x28 bytes);
 * SetLineG2 uses two vertices (0x14 bytes). */
typedef struct MenuLineVertex {
    SpriteColor color;
    u16 x;
    u16 y;
} MenuLineVertex;

typedef struct MenuLineG4 {
    u32 tag;
    MenuLineVertex vertices[4];
    u32 end;
} MenuLineG4;

typedef struct MenuLineG2 {
    u32 tag;
    MenuLineVertex vertices[2];
} MenuLineG2;

/* Shared scratchpad layout used by the two menu line builders. */
typedef struct MenuLineScratch {
    u8 pad_00[0x24];
    union { u32 *words; u8 *bytes; } order_table;
    u8 pad_28[0x4C];
    s16 vertices[4][4];
    s32 interp;
    s32 flag;
    u8 pad_9C[0x28];
    s32 depth;
    u8 pad_C8[0x20];
    u16 screen[4][2];
} MenuLineScratch;

void draw_random_tinted_quad_pair(u8 *effect);
void draw_random_colored_line(s32 end_point, s32 start_point);

#endif

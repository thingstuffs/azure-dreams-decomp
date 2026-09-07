#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} Rect;

typedef struct {
    s16 height;
    u16 y;
    u16 flags;
} Tile;

extern s32 func_800A6D30(void);
extern u8 D_8008333C[32];
extern u8 D_800EA000[];

void func_8001CEC0(Rect *rect)
{
    u8 *dungeon = D_8008333C;
    s32 parity;
    s32 x_end;
    s32 y_end;
    s32 x;
    s32 y;
    register s32 initial_y ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 initial_x;
    register s32 initial_width ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 initial_height;
    s32 y_parity;
    u16 flags;
    u16 flags_copy;
    u16 tile_y;
    volatile Tile *tile;

    parity = func_800A6D30() & 1;
    initial_y = rect->y;
    initial_x = rect->x;
    initial_width = rect->width;
    ASM_KEEP4(initial_y, initial_x, initial_width, rect);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    y = initial_y;
    initial_height = rect->height;
    x_end = initial_x + initial_width;
    y_end = y + initial_height;

    if (y < y_end) {
        do {
            x = rect->x;
            if (x < x_end) {
                y_parity = y & 1;
                do {
                    if (((x & 1) == parity) && (y_parity == parity)) {
                        tile = (volatile Tile *) (D_800EA000 +
                            (((y << *(s16 *)(dungeon + 0x14)) + x) * 6));
                        flags = tile->flags;
                        flags_copy = tile->flags;
                        tile->height = (flags >> 1) + 0x63;
                        tile_y = tile->y;
                        tile->flags = flags_copy | 0x8000;
                        tile->y = tile_y - 0x60;
                    }
                    x++;
                } while (x < x_end);
            }
            y++;
        } while (y < y_end);
    }
}

/* MECHANISM: Hold the input in s0 and the D_8008333C byte base in s1 across the call.
   Signed-width loop counters avoid truncation masks; a six-byte Tile gives byte indexing.
   Split the flags reread and later y read into distinct RMW live ranges to match scheduling. */

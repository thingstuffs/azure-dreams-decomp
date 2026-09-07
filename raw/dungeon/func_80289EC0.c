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
    register s32 parity ASM_REG("$8");
    register s32 x_end ASM_REG("$9");
    register s32 y_end ASM_REG("$10");
    register s32 x ASM_REG("$5");
    register s32 y ASM_REG("$6");
    register s32 initial_y ASM_REG("$3");
    register s32 initial_x ASM_REG("$4");
    register s32 initial_width ASM_REG("$2");
    register s32 initial_height ASM_REG("$3");
    register s32 y_parity ASM_REG("$7");
    u16 flags;
    u16 flags_copy;
    u16 tile_y;
    volatile Tile *tile;

    parity = func_800A6D30() & 1;
    initial_y = rect->y;
    initial_x = rect->x;
    initial_width = rect->width;
    ASM_KEEP4(initial_y, initial_x, initial_width, rect);
    y = initial_y;
    initial_height = rect->height;
    ASM_KEEP(initial_height);
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

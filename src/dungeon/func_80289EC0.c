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

extern s32 func_800A6D30(Rect *, s32, s32, s32);
extern u8 D_8008333C[32];
extern u8 D_800EA000[];

/* Adjust tile heights and flags where both coordinates match a random parity. */
void func_8001CEC0(Rect *rect, s32 rng_input_1, s32 rng_input_2, s32 rng_input_3)
{
    u8 *dungeon = D_8008333C;
    s32 parity;
    s32 x_end;
    s32 y_end;
    s32 x;
    s32 y;
    register s32 initial_y ASM_REG("$3");
    s32 initial_x;
    register s32 initial_width ASM_REG("$2");
    s32 initial_height;
    s32 y_parity;
    u16 flags;
    u16 saved_flags;
    u16 tile_y;
    volatile Tile *tile;

    parity = func_800A6D30(rect, rng_input_1, rng_input_2, rng_input_3) & 1;
    initial_y = rect->y;
    initial_x = rect->x;
    initial_width = rect->width;
    ASM_KEEP4(initial_y, initial_x, initial_width, rect);
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
                        saved_flags = tile->flags;
                        tile->height = (flags >> 1) + 0x63;
                        tile_y = tile->y;
                        tile->flags = saved_flags | 0x8000;
                        tile->y = tile_y - 0x60;
                    }
                    x++;
                } while (x < x_end);
            }
            y++;
        } while (y < y_end);
    }
}

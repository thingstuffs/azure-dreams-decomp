#include "common.h"
#include "shared/game_work.h"

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
extern u8 D_800EA000[];

/* Adjust tile heights and flags where both coordinates match a random parity. */
void func_8001CEC0(Rect *rect, s32 rng_input_1, s32 rng_input_2, s32 rng_input_3)
{
    MapGrid *dungeon = &gameWork.map;
    s32 parity;
    s32 x_end;
    s32 y_end;
    s32 x;
    s32 y;
    s32 initial_y;
    s32 initial_x;
    s32 initial_width;
    s32 initial_height;
    s32 y_parity;
    Tile *tile;

    parity = func_800A6D30() & 1;
    initial_y = rect->y;
    initial_x = rect->x;
    initial_width = rect->width;
    initial_height = rect->height;
    x_end = initial_x + initial_width;
    y_end = initial_y + initial_height;
    y = initial_y;

    if (y < y_end) {
        do {
            x = rect->x;
            if (x < x_end) {
                y_parity = y & 1;
                do {
                    if (((x & 1) == parity) && (y_parity == parity)) {
                        tile = (Tile *) (D_800EA000 +
                            (((y << dungeon->shiftX) + x) * 6));
                        tile->height = (tile->flags >> 1) + 0x63;
                        tile->y -= 0x60;
                        tile->flags |= 0x8000;
                    }
                    x++;
                } while (x < x_end);
            }
            y++;
        } while (y < y_end);
    }
}

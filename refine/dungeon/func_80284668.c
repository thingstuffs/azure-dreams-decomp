#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern u8 D_8008333C[32];
extern u8 D_800EA000[];


/* Fill the third field of each grid cell in a rectangle with the given value. */
void func_80017668(s16 start_x, s16 y, s16 width, s32 height, u16 fill_value) {
    s32 rows_left;
    register u16 cell_value ASM_REG("$11");   /* MATCH pin: retail register colouring depends on it */
    register s32 span_left ASM_REG("$7") = height;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 width_shifted ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    s32 start_x_shifted;
    s32 x;
    register s32 row_y;
    s16 *grid_settings;
    s32 next_rows_left;
    s32 cell_index;
    u16 *cell;

    rows_left = height;
    do { cell_value = fill_value; } while (0);
    grid_settings = (s16 *)D_8008333C;
    span_left <<= 16;
    if (span_left > 0) {
        width_shifted = width << 16;
        start_x_shifted = start_x << 16;
        do {
            span_left = width_shifted >> 16;
            x = start_x_shifted >> 16;
            if (span_left > 0) {
                row_y = y;
                do {
                    span_left--;
                    cell_index = grid_settings[10];
                    cell_index = row_y << cell_index;
                    cell_index += x;
                    x++;
                    cell = (u16 *)(D_800EA000 + cell_index * 6);
                    cell[2] = cell_value;
                } while (span_left > 0);
            }
            next_rows_left = rows_left - 1;
            rows_left = next_rows_left;
            ASM_KEEP(next_rows_left);   /* MATCH pin: load-bearing for the whole function shape */
            y++;
        } while ((next_rows_left << 16) > 0);
    }
}

/* MECHANISM: Frameless leaf with pinned argument/live-range roles reproduces the retail temporaries.
   ASM_KEEP(next_rows_left) after the rows_left decrement blocks CSE from substituting $t2,
   preserving retail's final sll $v0,$v0,16 at word 28. */

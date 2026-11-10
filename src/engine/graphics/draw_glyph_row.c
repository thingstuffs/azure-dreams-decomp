#include "common.h"
#include "engine/graphics.h"

#include "common.h"


/* Draw a zero-terminated sequence of two-byte glyph codes in a horizontal row. */
void draw_glyph_row(s32 x, s32 y, s32 spacing_index, u8 *glyph_codes)
{
    u8 *cursor = glyph_codes;
    s32 column = 0;
    s32 spacing = spacing_index;

    if (*cursor == 0) {
        return;
    }

    do {
        move_glyph_to_grid_position(cursor, (s16)column, 0, spacing & 0xFF,
                      (s16)x, (s16)y, 1);
        cursor += 2;
        column++;
    } while (*cursor != 0);
}

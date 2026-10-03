#include "common.h"

#include "common.h"

extern void func_8003AB44(u8 *glyph_codes, s16 column, s16 row, s32 spacing,
                          s16 x, s32 y, s32 value);

/* Draw a zero-terminated sequence of two-byte glyph codes in a horizontal row. */
void func_8003AC1C(s32 x, s32 y, s32 spacing_index, u8 *glyph_codes)
{
    u8 *cursor = glyph_codes;
    s32 column = 0;
    s32 spacing = spacing_index;

    if (*cursor == 0) {
        return;
    }

    do {
        func_8003AB44(cursor, (s16)column, 0, spacing & 0xFF,
                      (s16)x, (s16)y, 1);
        cursor += 2;
        column++;
    } while (*cursor != 0);
}

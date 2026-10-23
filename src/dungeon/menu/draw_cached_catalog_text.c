#include "common.h"
#include "dungeon/menu.h"
/* cfail-repair: tf7-phase1-cache-v3 */
s32 LoadTPage(void *, s32, s32, s32, s32, s32, s32); /* extern */
s32 get_cached_catalog_glyph();                             /* extern */

typedef struct S_801239B8_0 {
    u8 unk_00;
    u8 unk_01;
} S_801239B8_0;

/* Draws a zero-terminated sequence of two-byte character codes at successive horizontal positions. */
void draw_cached_catalog_text(u8 *text, s16 start_x, s16 y) {
    s16 x;
    s32 glyph;
    u8 *cursor;
    u8 code_hi;
    u8 code_lo;

    cursor = text;
    x = start_x;
    if (*cursor != 0) {
        do {
            code_hi = ((S_801239B8_0 *)cursor)->unk_00;
            code_lo = ((S_801239B8_0 *)cursor)->unk_01;
            cursor += 2;
            glyph = get_cached_catalog_glyph(code_lo | (code_hi << 8));
            if (glyph != 0) {
                LoadTPage(glyph, 0, 0, x, (s32) y, 0xC, 0x10);
                x += 3;
            }
        } while (*cursor != 0);
    }
}

#include "common.h"
#include "m2c_compat.h"
#include "dungeon/menu.h"
#include "town/menu.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 DrawSync(s32);
extern s32 ClearImage(s16 *, s32, s32, s32);
extern M2C_UNK D_8011ACD8;
extern s32 catalog_glyphs[];

typedef struct S_80123A60_0 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_80123A60_0;   /* arg0 in draw_catalog_entry_page */

/* Draws available entries for the selected group at fixed screen positions. */
void draw_catalog_entry_page(S_80123A60_0 *state) {
    s16 draw_rect[4];
    s32 *entry;
    s32 *entry_table;
    s32 *entry_table_2;
    s32 *entry_table_3;
    s32 entry_id;
    s32 slot;
    s32 group;

    draw_rect[0] = 0x180;
    draw_rect[1] = 0x80;
    draw_rect[2] = 0x36;
    draw_rect[3] = 0x60;
    ClearImage(draw_rect, 0, 0, 0);
    draw_cached_catalog_text(&D_8011ACD8, 0x192, 0xD0);
    DrawSync(0);
    slot = 0;
    if (state->unk_0F == 3) {
        s32 page;

        page = state->unk_0F;
        entry_id = page * 0x10;
        if (is_catalog_entry_available(entry_id & 0xF0) & 0xFF) {
            entry_table = &catalog_glyphs;
            draw_vram_glyph_text(*(((page * 0x20) + entry_id) + entry_table), 0x180, 0x80);
        }
        entry_id += 1;
        if (is_catalog_entry_available(entry_id & 0xFF) & 0xFF) {
            entry_table_2 = &catalog_glyphs;
            draw_vram_glyph_text(*((entry_id * 3) + entry_table_2), 0x1A4, 0xA0);
        }
        DrawSync(0);
        return;
    }
    group = state->unk_0F;
    entry_id = group * 0x10;
    entry_table_3 = &catalog_glyphs;
    entry = ((group * 0x20) + entry_id) + entry_table_3;
    do {
        if (is_catalog_entry_available(entry_id & 0xFF) & 0xFF) {
            draw_vram_glyph_text(*entry, (s16) (((slot % 3) * 0x12) + 0x180), (s16) (((slot / 3) * 0x10) + 0x80));
        }
        slot += 1;
        entry += 3;
        entry_id += 1;
    } while (slot < 0x10);
    DrawSync(0);
}

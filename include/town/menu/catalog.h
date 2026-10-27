#ifndef TOWN_MENU_CATALOG_H
#define TOWN_MENU_CATALOG_H

/* The two catalog cursor handlers dispatch these phases from object +4.
 * They populate the entry number, hide the cursor, then position it. */
enum CatalogCursorPhase {
    CATALOG_CURSOR_NUMBER = 1,
    CATALOG_CURSOR_HIDE = 2,
    CATALOG_CURSOR_POSITION = 3,
};

#include "common.h"

typedef struct CatalogDisplay {
    u8 pad_00[0x54];
    s32 last_node;
    s32 **nodes;
} CatalogDisplay;

s32 initialize_catalog_display_nodes(CatalogDisplay *display);
void initialize_catalog_state(void *state);

s16 *get_cached_catalog_glyph(s16 char_code);
void draw_cached_catalog_text(u8 *text, s16 x, s16 y);
void draw_vram_glyph_text(u8 *text, s16 x, s16 y);

#endif

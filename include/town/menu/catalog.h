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

struct ItemMenuPart;

typedef struct CatalogDisplay {
    u8 pad_00[4];
    union { s16 as_s16; u16 as_u16; } unk_04;
    s16 unk_06;
    s16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 unk_17;
    u8 unk_18;
    u8 pad_19[0x3B];
    struct ItemMenuPart *last_node;
    struct ItemMenuPart **nodes;
} CatalogDisplay;

s32 initialize_catalog_display_nodes(CatalogDisplay *display);
void initialize_catalog_state(CatalogDisplay *state);

s16 *get_cached_catalog_glyph(s16 char_code);
void draw_cached_catalog_text(u8 *text, s16 x, s16 y);
void draw_vram_glyph_text(u8 *text, s16 x, s16 y);

#endif

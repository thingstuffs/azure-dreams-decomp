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
struct CatalogNodeSlots;

typedef struct CatalogDisplay {
    u8 pad_00[4];
    u16 unk_04;
    s16 unk_06;
    u16 unk_08;
    u8 unk_0A; /* catalog dispatch phase, stored through both byte views */
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
    /* Detail input indexes either of the adjacent selection bytes. */
    u8 choices[2];
    u8 pad_19[0x3B];
    struct ItemMenuPart *last_node;
    /* Both views describe the same 98-pointer table. Slot 97 is the cursor. */
    union {
        struct ItemMenuPart **nodes;
        struct CatalogNodeSlots *table;
    } parts;
} CatalogDisplay;

void select_paired_value_tables(CatalogDisplay *selection);
void draw_catalog_entry_page(CatalogDisplay *display);
void enter_catalog_grid(CatalogDisplay *display);
void animate_catalog_grid_to_detail(CatalogDisplay *display);
void animate_catalog_detail_to_grid(CatalogDisplay *display);
void animate_catalog_next_detail(CatalogDisplay *display);
void animate_catalog_previous_detail(CatalogDisplay *display);
void refresh_catalog_entry_grid(CatalogDisplay *menu);
void refresh_catalog_primary_detail(CatalogDisplay *display);
void refresh_catalog_secondary_detail(CatalogDisplay *display);
void draw_catalog_primary_detail(CatalogDisplay *display);
void draw_catalog_secondary_detail(CatalogDisplay *display);
void swap_catalog_paired_entries(CatalogDisplay *display);

s32 initialize_catalog_display_nodes(CatalogDisplay *display);
void initialize_catalog_state(CatalogDisplay *state);

s16 *build_filtered_catalog_glyph(s32 char_code, s16 *destination);
void draw_cached_catalog_text(u8 *text, s16 x, s16 y);
void draw_vram_glyph_text(u8 *text, s16 x, s16 y);

void load_catalog_adjacent_detail_texture(CatalogDisplay *display);
void load_catalog_detail_texture(CatalogDisplay *display);
void finish_catalog_return_to_grid(CatalogDisplay *display);
void reset_catalog_grid_input(CatalogDisplay *display);
void scroll_catalog_text_up(CatalogDisplay *display);
void update_catalog(CatalogDisplay *display);
void update_catalog_scroll_indicators(CatalogDisplay *display);
void refresh_catalog_scroll_indicators(CatalogDisplay *display);
void enter_catalog_detail_input(CatalogDisplay *display);
void finish_catalog_detail_opening(CatalogDisplay *display);
void finish_catalog_detail_transition(CatalogDisplay *display);
void handle_catalog_detail_input(CatalogDisplay *display);
void reset_catalog_scroll_indicators(CatalogDisplay *display);
void update_catalog_scroll_availability(CatalogDisplay *display);

extern void (*D_80126B34[])(CatalogDisplay *);
extern void (*catalog_callbacks[])(CatalogDisplay *);

#endif

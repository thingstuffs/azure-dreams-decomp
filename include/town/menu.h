#ifndef TOWN_MENU_H
#define TOWN_MENU_H

#include "common.h"


/* draw_vram_glyph_text.c */
void draw_vram_glyph_text(u8 *text, s16 start_x, s16 y);


/* draw_cached_catalog_text.c */
void draw_cached_catalog_text(u8 *text, s16 x, s16 y);

void initialize_item_menu_state(u8 *owner, s32 base_value);

struct MenuResourceOwner;
s32 load_menu_display_resource(struct MenuResourceOwner *, s32);

#endif

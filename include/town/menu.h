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

/* Callback entry points. */
void decrement_target_halfword_by_four(void *unused_0, void *unused_1, void *target);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct func_8009F880_S_8009CFE0_0;
s32 classify_object_against_bounds(struct func_8009F880_S_8009CFE0_0 *object, void *position_data);

void initialize_object_transform_and_state(s32 slot_id, void *object, s32 object_id);

void create_indexed_effect_object(s32 index, s32 kind);

#endif

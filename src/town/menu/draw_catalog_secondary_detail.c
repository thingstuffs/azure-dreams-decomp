#include "common.h"
#include "town/menu/catalog.h"
#include "town/menu.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"
#include "town/data.h"
#include "town/menu/catalog_detail_data.h"
#include "town/menu/catalog_glyph_data.h"

#include "sdk/libgpu_types.h"

/* Clear display regions and draw the selected entry images and numbered label. */
void draw_catalog_secondary_detail(CatalogDisplay *state)
{
    RECT clear_rect;
    char label[16];
    char number_text[5];
    CatalogDetailImageList *image_lists;
    char *label_cursor;
    s32 pos;
    u8 entry_index;

    clear_rect.x = 0x1C0;
    clear_rect.y = 0x90;
    clear_rect.w = 0x38;
    clear_rect.h = 0x10;
    ClearImage(&clear_rect, 0, 0, 0);

    clear_rect.y = 0xC0;
    clear_rect.w = 0x1E;
    clear_rect.x = 0x1C0;
    clear_rect.h = 0x20;
    ClearImage(&clear_rect, 0, 0, 0);

    clear_rect.x = 0x2C0;
    clear_rect.w = 0x3E;
    clear_rect.y = 0;
    clear_rect.h = 0xF0;
    ClearImage(&clear_rect, 0, 0, 0);

    entry_index = state->unk_14;
    draw_cached_catalog_text(catalog_glyphs[entry_index].image, 0x1C0, 0x90);
    draw_vram_glyph_text(catalog_habitat_label, 0x1C7, 0xC0);

    entry_index = state->unk_14;
    draw_vram_glyph_text(*catalog_glyphs[entry_index].image_ref,
                  (s16)(0x1CF - catalog_glyphs[entry_index].label_width), 0xD0);

    entry_index = state->unk_14;
    pos = 0;
    if (catalog_detail_images[entry_index].count != 0) {
        image_lists = catalog_detail_images;
        do {
            draw_vram_glyph_text(image_lists[entry_index].images[pos], 0x2C0, (s16)(pos * 0x10));
            if ((pos & 1) || (pos < (image_lists[state->unk_14].count - 1))) {
                DrawSync(0);
            }
            pos++;
            entry_index = state->unk_14;
        } while (pos < image_lists[entry_index].count);
    }
    DrawSync(0);

    pos = 10;
    label_cursor = &label[10];
    do {
        *label_cursor = 0;
        pos--;
        label_cursor--;
    } while (pos >= 0);

    strcat(label, catalog_number_prefix);
    number_text[0] = 0x82;
    number_text[1] = ((state->unk_14 + 1) / 10) + 0x4F;
    number_text[2] = 0x82;
    number_text[3] = ((state->unk_14 + 1) % 10) + 0x4F;
    number_text[4] = 0;
    strcat(label, number_text);
    draw_cached_catalog_text(label, 0x1DB, 0x90);
    DrawSync(0);
}

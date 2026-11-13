#include "common.h"
#include "m2c_compat.h"
#include "town/menu/catalog.h"
#include "town/menu/catalog_glyph_data.h"
#include "town/menu.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_types.h"
extern u8 D_8011ACD8;


/* Clears the image area and draws available images for the object's category. */
void draw_catalog_entry_page(CatalogDisplay *object_data) {
    CatalogDisplay *object = object_data; /* Retains the retail register allocation. */
    RECT clear_rect;
    CatalogGlyphEntry *image_entry;
    CatalogGlyphEntry *glyphs;
    s32 second_image_id;
    s32 image_id;
    s32 slot;
    s16 grid_category;
    s32 category;
    u8 test_category;

    clear_rect.x = 0x180;
    clear_rect.y = 0x80;
    clear_rect.w = 0x36;
    clear_rect.h = 0x60;
    ClearImage(&clear_rect, 0, 0, 0);
    draw_cached_catalog_text(&D_8011ACD8, 0x192, 0xD0);
    DrawSync(0);
    category = object->unk_0F;
    test_category = category;
    slot = 0;
    if (test_category == 3) {
        slot = category;
        second_image_id = slot * 0x10;
        if (is_catalog_entry_available(second_image_id & 0xF0) & 0xFF) {
            draw_vram_glyph_text(catalog_glyphs[second_image_id].image, 0x180, 0x80);
        }
        second_image_id += 1;
        if (is_catalog_entry_available(second_image_id & 0xFF) & 0xFF) {
            draw_vram_glyph_text(catalog_glyphs[second_image_id].image, 0x1A4, 0xA0);
        }
    } else {
        grid_category = object->unk_0F;
        glyphs = catalog_glyphs;
        image_id = grid_category * 0x10;
        image_entry = &glyphs[image_id];
        do {
            if (is_catalog_entry_available(image_id & 0xFF) & 0xFF) {
                draw_vram_glyph_text(image_entry->image, (s16) (((slot % 3) * 0x12) + 0x180),
                    (s16) (((slot / 3) * 0x10) + 0x80));
            }
            slot += 1;
            image_entry += 1;
            image_id += 1;
        } while (slot < 0x10);
    }
    DrawSync(0);
}

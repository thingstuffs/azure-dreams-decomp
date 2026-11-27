#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "town/data.h"
#include "town/menu/catalog.h"



#include "sdk/libgpu_types.h"

extern u8 resource_completion_callback_address[];

/* Load a texture and its palette, then advance the loader after upload. */
void load_catalog_detail_texture(CatalogDisplay *loader_arg)
{
    CatalogDisplay *loader = loader_arg;
    RECT texture_rect;
    RECT palette_rect;
    RECT *upload_rect;
    u32 *texture_pixels;
    void *compressed;
    void *pixels;
    s32 texture_height;
    s32 palette_rows;
    u8 load_state;

    load_state = loader->texture_load_phase;
    if (load_state != 0) {
        if (load_state != 1) {
            return;
        }
    } else {
        pack_tagged_resource_descriptor(8, catalog_texture_buffer, catalog_texture_request,
                      catalog_texture_resources[loader->selected_entry][1]);
        Control_CD(6, catalog_texture_request, 0);
        loader->texture_load_done = 0;
        Control_CD(0xFF, resource_completion_callback_address, &loader->texture_load_done);
        loader->texture_load_phase++;
    }
    if (loader->texture_load_done == 0) {
        return;
    }

    palette_rect.x = 0;
    palette_rect.y = loader->active_detail_slot + 0x1CA;
    palette_rect.w = 0x100;
    palette_rows = 1;
    palette_rect.h = palette_rows;
    LoadImage(&palette_rect, catalog_texture_buffer);

    compressed = catalog_texture_buffer + 0x80;
    pixels = catalog_texture_pixels;
    decompress_lz(compressed, pixels);

    upload_rect = &texture_rect;
    texture_pixels = catalog_texture_pixels;
    texture_height = 0x80;
    texture_rect.x = (loader->active_detail_slot << 6) + 0x240;
    texture_rect.y = texture_height;
    texture_rect.w = 0x40;
    texture_rect.h = texture_height;
    LoadImage(upload_rect, texture_pixels);

    ((CatalogDisplay *)((u8 *)loader + loader->active_detail_slot))->choices[0] =
        loader->selected_entry;
    loader->phase = 6;
    loader->texture_load_phase = 0;
    loader->transition_frame = palette_rows;
    loader->transition_duration = 0x19;
}


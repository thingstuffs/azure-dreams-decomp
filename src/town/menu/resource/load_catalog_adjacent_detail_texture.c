#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "town/data.h"
#include "town/menu/catalog.h"



#include "sdk/libgpu_types.h"

extern u8 resource_completion_callback_address[];

/* Loads an image and palette into VRAM, then updates the loading state. */
void load_catalog_adjacent_detail_texture(CatalogDisplay *context_arg) {
    CatalogDisplay *context = context_arg;
    RECT image_rect;
    RECT palette_rect;
    void *compressed;
    void *pixels;
    u8 load_phase;

    load_phase = context->texture_load_phase;
    if (load_phase != 0) {
        if (load_phase != 1) {
            return;
        }
    } else {
        pack_tagged_resource_descriptor(8, catalog_texture_buffer, catalog_texture_request,
                      catalog_texture_resources[context->selected_entry][1]);
        Control_CD(6, catalog_texture_request, 0);
        context->texture_load_done = 0;
        Control_CD(0xFF, resource_completion_callback_address, &context->texture_load_done);
        context->texture_load_phase++;
    }
    if (context->texture_load_done == 0) {
        return;
    }

    palette_rect.x = 0;
    palette_rect.y = context->active_detail_slot + 0x1CA;
    palette_rect.w = 0x100;
    palette_rect.h = 1;
    LoadImage(&palette_rect, catalog_texture_buffer);

    compressed = catalog_texture_buffer + 0x80;
    pixels = catalog_texture_pixels;
    decompress_lz(compressed, pixels);

    image_rect.x = (context->active_detail_slot << 6) + 0x240;
    image_rect.y = 0x80;
    image_rect.w = 0x40;
    image_rect.h = 0x80;
    LoadImage(&image_rect, catalog_texture_pixels);

    ((CatalogDisplay *)((u8 *)context + context->active_detail_slot))->choices[0] =
        context->selected_entry;

    {
        u32 state_value = context->selected_entry;
        u32 index_limit = context->previous_entry;

        state_value = state_value < index_limit;
        if (state_value == 0) {
            context->phase = 0xB;
        } else {
            context->phase = 0xA;
        }
        context->transition_frame = 1;
    }
    context->texture_load_phase = 0;
    context->transition_duration = 0x19;
}

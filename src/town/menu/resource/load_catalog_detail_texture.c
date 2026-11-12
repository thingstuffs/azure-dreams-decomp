#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "town/data.h"
#include "town/menu/catalog.h"



#include "sdk/libgpu_types.h"

extern s32 resource_completion_callback_address[];

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

    load_state = loader->unk_0B;
    if (load_state != 0) {
        if (load_state != 1) {
            return;
        }
    } else {
        pack_tagged_resource_descriptor(8, catalog_texture_buffer, catalog_texture_request,
                      catalog_texture_resources[loader->unk_13][1]);
        Control_CD(6, catalog_texture_request, 0);
        loader->unk_0D = 0;
        Control_CD(0xFF, resource_completion_callback_address, (u8 *)loader + 0xD);
        loader->unk_0B++;
    }
    if (loader->unk_0D == 0) {
        return;
    }

    palette_rect.x = 0;
    palette_rect.y = loader->unk_16 + 0x1CA;
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
    texture_rect.x = (loader->unk_16 << 6) + 0x240;
    texture_rect.y = texture_height;
    texture_rect.w = 0x40;
    texture_rect.h = texture_height;
    LoadImage(upload_rect, texture_pixels);

    ((CatalogDisplay *)((u8 *)loader + loader->unk_16))->choices[0] =
        loader->unk_13;
    loader->unk_0A = 6;
    loader->unk_0B = 0;
    loader->unk_04 = palette_rows;
    loader->unk_06 = 0x19;
}


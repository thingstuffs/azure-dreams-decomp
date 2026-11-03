#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "town/data.h"
#include "town/menu/catalog.h"

typedef struct S_801254D8_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x1];
    u8 unk_0D;
    u8 pad_0E[0x5];
    u8 unk_13;
    u8 unk_14;
    u8 pad_15[0x1];
    u8 unk_16;
} S_801254D8_0;   /* arg0 in load_catalog_adjacent_detail_texture */

typedef struct S_801254D8_1 {
    u8 pad_00[0x17];
    u8 unk_17;
} S_801254D8_1;   /* (u8 *)arg0 + ((S_801254D8_0 *)arg0)->unk_16 in load_catalog_adjacent_detail_texture */


typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern s32 resource_completion_callback_address[];

/* Loads an image and palette into VRAM, then updates the loading state. */
void load_catalog_adjacent_detail_texture(CatalogDisplay *context_arg) {
    CatalogDisplay *context = context_arg;
    Rect image_rect;
    Rect palette_rect;
    void *compressed;
    void *pixels;
    u8 load_phase;

    load_phase = context->unk_0B.as_u8;
    if (load_phase != 0) {
        if (load_phase != 1) {
            return;
        }
    } else {
        pack_tagged_resource_descriptor(8, catalog_texture_buffer, catalog_texture_request,
                      catalog_texture_resources[context->unk_13.as_u8][1]);
        Control_CD(6, catalog_texture_request, 0);
        context->unk_0D = 0;
        Control_CD(0xFF, resource_completion_callback_address, (u8 *)context + 0xD);
        context->unk_0B.as_u8++;
    }
    if (context->unk_0D == 0) {
        return;
    }

    palette_rect.x = 0;
    palette_rect.y = context->unk_16 + 0x1CA;
    palette_rect.w = 0x100;
    palette_rect.h = 1;
    LoadImage(&palette_rect, catalog_texture_buffer);

    compressed = catalog_texture_buffer + 0x80;
    pixels = catalog_texture_pixels;
    decompress_lz(compressed, pixels);

    image_rect.x = (context->unk_16 << 6) + 0x240;
    image_rect.y = 0x80;
    image_rect.w = 0x40;
    image_rect.h = 0x80;
    LoadImage(&image_rect, catalog_texture_pixels);

    ((S_801254D8_1 *)((u8 *)context + context->unk_16))->unk_17 =
        context->unk_13.as_u8;

    {
        u32 state_value = context->unk_13.as_u8;
        u32 index_limit = context->unk_14;

        state_value = state_value < index_limit;
        if (state_value == 0) {
            context->unk_0A.as_s8 = 0xB;
        } else {
            context->unk_0A.as_s8 = 0xA;
        }
        context->unk_04.as_s16 = 1;
    }
    context->unk_0B.as_u8 = 0;
    context->unk_06.as_s16 = 0x19;
}

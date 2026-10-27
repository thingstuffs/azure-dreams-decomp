#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"

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

extern s32 Control_CD();
extern s32 pack_tagged_resource_descriptor();

extern s32 resource_completion_callback_address[];
extern s32 *catalog_texture_resources[];
extern u32 catalog_texture_buffer[];
extern u32 catalog_texture_pixels[];
extern u8 catalog_texture_request[];


/* Loads an image and palette into VRAM, then updates the loading state. */
void load_catalog_adjacent_detail_texture(void *context) {
    Rect image_rect;
    Rect palette_rect;
    void *compressed;
    void *pixels;
    u8 load_phase;

    load_phase = ((S_801254D8_0 *)context)->unk_0B;
    if (load_phase != 0) {
        if (load_phase != 1) {
            return;
        }
    } else {
        pack_tagged_resource_descriptor(8, catalog_texture_buffer, catalog_texture_request,
                      catalog_texture_resources[((S_801254D8_0 *)context)->unk_13][1]);
        Control_CD(6, catalog_texture_request, 0);
        ((S_801254D8_0 *)context)->unk_0D = 0;
        Control_CD(0xFF, resource_completion_callback_address, (u8 *)context + 0xD);
        ((S_801254D8_0 *)context)->unk_0B++;
    }
    if (((S_801254D8_0 *)context)->unk_0D == 0) {
        return;
    }

    palette_rect.x = 0;
    palette_rect.y = ((S_801254D8_0 *)context)->unk_16 + 0x1CA;
    palette_rect.w = 0x100;
    palette_rect.h = 1;
    LoadImage(&palette_rect, catalog_texture_buffer);

    compressed = catalog_texture_buffer + 0x80;
    pixels = catalog_texture_pixels;
    decompress_lz(compressed, pixels);

    image_rect.x = (((S_801254D8_0 *)context)->unk_16 << 6) + 0x240;
    image_rect.y = 0x80;
    image_rect.w = 0x40;
    image_rect.h = 0x80;
    LoadImage(&image_rect, catalog_texture_pixels);

    ((S_801254D8_1 *)((u8 *)context + ((S_801254D8_0 *)context)->unk_16))->unk_17 =
        ((S_801254D8_0 *)context)->unk_13;

    {
        u32 state_value = ((S_801254D8_0 *)context)->unk_13;
        u32 index_limit = ((S_801254D8_0 *)context)->unk_14;

        state_value = state_value < index_limit;
        if (state_value == 0) {
            ((S_801254D8_0 *)context)->unk_0A = 0xB;
        } else {
            ((S_801254D8_0 *)context)->unk_0A = 0xA;
        }
        ((S_801254D8_0 *)context)->unk_04 = 1;
    }
    ((S_801254D8_0 *)context)->unk_0B = 0;
    ((S_801254D8_0 *)context)->unk_06 = 0x19;
}

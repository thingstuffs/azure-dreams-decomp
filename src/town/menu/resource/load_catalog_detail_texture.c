#include "common.h"
#include "engine/graphics.h"

typedef struct S_80124DB0_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    u8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x1];
    u8 unk_0D;
    u8 pad_0E[0x5];
    u8 unk_13;
    u8 pad_14[0x2];
    u8 unk_16;
} S_80124DB0_0;   /* arg0 in load_catalog_detail_texture */

typedef struct S_80124DB0_1 {
    u8 pad_00[0x17];
    u8 unk_17;
} S_80124DB0_1;   /* (u8 *)arg0 + ((S_80124DB0_0 *)arg0)->unk_16 in load_catalog_detail_texture */


typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern void Control_CD();
extern void pack_tagged_resource_descriptor();
extern void LoadImage();

extern s32 resource_completion_callback_address[];
extern s32 *catalog_texture_resources[];
extern u8 catalog_texture_buffer[];
extern u8 catalog_texture_pixels[];
extern u8 catalog_texture_request[];

/* Load a texture and its palette, then advance the loader after upload. */
void load_catalog_detail_texture(void *loader)
{
    Rect texture_rect;
    Rect palette_rect;
    Rect *upload_rect;
    u8 *texture_pixels;
    s32 texture_height;
    s32 palette_rows;
    u8 load_state;

    load_state = ((S_80124DB0_0 *)loader)->unk_0B;
    if (load_state != 0) {
        if (load_state != 1) {
            return;
        }
    } else {
        pack_tagged_resource_descriptor(8, catalog_texture_buffer, catalog_texture_request,
                      catalog_texture_resources[((S_80124DB0_0 *)loader)->unk_13][1]);
        Control_CD(6, catalog_texture_request, 0);
        ((S_80124DB0_0 *)loader)->unk_0D = 0;
        Control_CD(0xFF, resource_completion_callback_address, (u8 *)loader + 0xD);
        ((S_80124DB0_0 *)loader)->unk_0B++;
    }
    if (((S_80124DB0_0 *)loader)->unk_0D == 0) {
        return;
    }

    palette_rect.x = 0;
    palette_rect.y = ((S_80124DB0_0 *)loader)->unk_16 + 0x1CA;
    palette_rect.w = 0x100;
    palette_rows = 1;
    palette_rect.h = palette_rows;
    LoadImage(&palette_rect, catalog_texture_buffer);

    decompress_lz(catalog_texture_buffer + 0x200, catalog_texture_pixels);

    upload_rect = &texture_rect;
    texture_pixels = catalog_texture_pixels;
    texture_height = 0x80;
    texture_rect.x = (((S_80124DB0_0 *)loader)->unk_16 << 6) + 0x240;
    texture_rect.y = texture_height;
    texture_rect.w = 0x40;
    texture_rect.h = texture_height;
    LoadImage(upload_rect, texture_pixels);

    ((S_80124DB0_1 *)((u8 *)loader + ((S_80124DB0_0 *)loader)->unk_16))->unk_17 =
        ((S_80124DB0_0 *)loader)->unk_13;
    ((S_80124DB0_0 *)loader)->unk_0A = 6;
    ((S_80124DB0_0 *)loader)->unk_0B = 0;
    ((S_80124DB0_0 *)loader)->unk_04 = palette_rows;
    ((S_80124DB0_0 *)loader)->unk_06 = 0x19;
}


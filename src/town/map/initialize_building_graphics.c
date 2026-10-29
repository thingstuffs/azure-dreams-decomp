#include "shared/runtime_dispatch.h"
#include "common.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "town/map.h"

typedef struct S_800B6FB8_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800B6FB8_0;   /* draw in initialize_building_graphics */


typedef struct S_800B6FB8_2 {
    u8 pad_00[0x1DC];
    void * unk_1DC;
} S_800B6FB8_2;   /* base in initialize_building_graphics */

extern u8 g_game_work[], building_texture_frame_zero[], building_texture_backup[], building_palette_backup[], D_8012F004[], town_tile_grid[];
extern u16 building_upload_rect[];
/* Initialize drawing state and upload image and palette data. */
void initialize_building_graphics(void)
{
    u8 *base, *status;
    u16 *image_rect, *first_rect, *palette_rect;
    u8 *image_data;
    S_800B6FB8_0 *draw;
    s32 width, color, draw_setting;
    u16 image_width;
    void *draw_buffer;

    image_rect = building_upload_rect;
    first_rect = image_rect;
    image_data = building_texture_frame_zero;
    base = g_game_work;
    draw = (S_800B6FB8_0 *)(base + 0x1DC);
    color = 0x7F;
    width = 0x2000;
    draw->unk_14 = 7;
    draw->unk_18 = color;
    draw->unk_1C = width;
    draw_setting = 7;
    draw->unk_16 = draw_setting;
    draw->unk_1A = color;
    draw->unk_1E = width;
    status = ((u8 *)&runtime_dispatch_state);

    building_upload_rect[0] = 0x328;
    image_rect[1] = 0x80;
    image_width = 8;
    image_rect[2] = image_width;
    image_rect[3] = 0x80;
    ((RuntimeDispatchState *)status)->flags16 &= 0xFFFE;
    StoreImage(first_rect, image_data);

    building_upload_rect[0] = 0x330;
    image_rect[1] = 0x80;
    image_rect[2] = image_width;
    image_rect[3] = 0x80;
    StoreImage(image_rect, building_texture_backup);

    palette_rect = building_upload_rect;
    building_upload_rect[0] = 0;
    palette_rect[1] = 0x1FB;
    palette_rect[2] = 0x40;
    palette_rect[3] = 1;
    StoreImage(palette_rect, building_palette_backup);
    DrawSync(0);

    draw_buffer = town_tile_grid;
    ((S_800B6FB8_2 *)base)->unk_1DC = draw_buffer;
    update_active_building_entries();
    runtime_load_packed_resource_chunks(0, D_8012F004);
}

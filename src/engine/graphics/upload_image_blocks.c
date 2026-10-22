#include "slus/owned_8004713C.h"

#include "slus/owned_8004713C.h"
#include "engine/graphics.h"

/* Uploads consecutive 0x2000-byte image blocks at offsets derived from the selected VRAM tile. */
void runtime_upload_image_blocks_vram_offsets_selected_tile_block_indices(s32 image_addr, s32 tile_id, s32 num_blocks) {
    s32 image_data;
    s32 block_index;
    s32 block_count;
    s32 tile;
    s32 tile_y_bits;
    RECT *rect;

    image_data = image_addr;
    block_index = 0;
    block_count = num_blocks;
    if ((block_count & 0xFFFF) != 0) {
        rect = (RECT *)&sound_idle_vsync_frame_alias[4];
        tile = tile_id & 0xFFFF;
        tile_y_bits = tile << 4;
loop_0:
        {
            s32 x = (tile << 6) & 0x3C0;
            if ((block_index / 2) != 0) {
                x += 0x20;
            }
            image_block_upload_x = x;
            {
                s32 y = tile_y_bits & 0x100;
                if ((block_index & 1) != 0) {
                    y += 0x80;
                }
                image_block_upload_y = y;
            }
            LoadImage(rect, (void *)image_data);
            block_index += 1;
            image_data += 0x2000;
        }
        if (block_index < (block_count & 0xFFFF))
            goto loop_0;
    }
}
s16 image_block_upload_x = 0;
s16 image_block_upload_y = 0;

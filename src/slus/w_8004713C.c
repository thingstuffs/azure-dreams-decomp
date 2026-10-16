#include "slus/owned_8004713C.h"

void runtimeUploadImageBlocksVRAMOffsetsSelectedTileBlockIndices(s32 image_addr, s32 tile_id, s32 num_blocks) {
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
        rect = (RECT *)&D_80080B00[4];
        tile = tile_id & 0xFFFF;
        tile_y_bits = tile << 4;
loop_0:
        {
            s32 x = (tile << 6) & 0x3C0;
            if ((block_index / 2) != 0) {
                x += 0x20;
            }
            D_80080B08 = x;
            {
                s32 y = tile_y_bits & 0x100;
                if ((block_index & 1) != 0) {
                    y += 0x80;
                }
                D_80080B0A = y;
            }
            LoadImage(rect, (void *)image_data);
            block_index += 1;
            image_data += 0x2000;
        }
        if (block_index < (block_count & 0xFFFF))
            goto loop_0;
    }
}

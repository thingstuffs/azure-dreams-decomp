#include "common.h"

#include "common.h"

typedef struct { s16 x, y, w, h; } RECT;

extern int LoadImage(RECT *rect, void *p);

/* Dual-access global: halfword stores via $gp scalars; LoadImage's rect
 * pointer is the absolute address of D_80080B08 (D_80080B00 declared at its
 * 8-byte extent: a view of <= 8 bytes keeps the unsplit la, one past it lands
 * on D_80080B08). */
extern s16 D_80080B08;
extern s16 D_80080B0A;
extern s16 D_80080B00[4];

/* Register pins force retail's saved-reg map: s3=full num_blocks (re-andi each
 * use), s2=tile, s4=tile<<4, s5=&rect. Without pins, 2.7.2 CSEs
 * (num_blocks & 0xFFFF) into a2 early and LICM-hoists tile<<6 into s3. */
/* Upload image blocks to VRAM at offsets selected by the tile and block indices. */
void func_8004713C(s32 image_addr, s32 tile_id, s32 num_blocks) {
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

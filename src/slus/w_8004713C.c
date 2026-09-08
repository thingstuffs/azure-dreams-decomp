#include "common.h"

#include "common.h"

typedef struct { s16 x, y, w, h; } RECT;

extern int LoadImage(RECT *rect, void *p);

/* Dual-access global: halfword stores via $gp scalars; LoadImage's rect
 * pointer is materialised with %hi/%lo via a >8B neighbour so address-of
 * is not gp_rel (D_80080B00[4] lands on D_80080B08 — same pattern as
 * w_8003F624.c). */
extern s16 D_80080B08;
extern s16 D_80080B0A;
extern s16 D_80080B00[8];

/* Register pins force retail's saved-reg map: s3=full num_blocks (re-andi each
 * use), s2=tile, s4=tile<<4, s5=&rect. Without pins, 2.7.2 CSEs
 * (num_blocks & 0xFFFF) into a2 early and LICM-hoists tile<<6 into s3. */
/* Upload image blocks to VRAM at offsets selected by the tile and block indices. */
void func_8004713C(s32 image_addr, s32 tile_id, s32 num_blocks) {
    s32 image_data;
    s32 block_index;
    register s32 block_count ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 tile ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 tile_y_bits;
    RECT *rect;

    image_data = image_addr;
    block_index = 0;
    block_count = num_blocks;
    if ((block_count & 0xFFFF) != 0) {
        rect = (RECT *)&D_80080B00[4];
        tile = tile_id & 0xFFFF;
        tile_y_bits = tile << 4;
        do {
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
        } while (block_index < (block_count & 0xFFFF));
    }
}

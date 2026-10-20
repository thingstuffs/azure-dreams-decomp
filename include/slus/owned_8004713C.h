#ifndef SLUS_OWNED_8004713C_H
#define SLUS_OWNED_8004713C_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

#include "common.h"

typedef struct { s16 x, y, w, h; } RECT;

extern int LoadImage(RECT *rect, void *p);

/* Dual-access global: halfword stores via $gp scalars; LoadImage's rect
 * pointer is the absolute address of D_80080B08 (D_80080B00 declared at its
 * 8-byte extent: a view of <= 8 bytes keeps the unsplit la, one past it lands
 * on D_80080B08). */
extern s16 image_block_upload_x;
extern s16 image_block_upload_y;
extern s16 sound_idle_vsync_frame_alias[4];

/* Register pins force retail's saved-reg map: s3=full num_blocks (re-andi each
 * use), s2=tile, s4=tile<<4, s5=&rect. Without pins, 2.7.2 CSEs
 * (num_blocks & 0xFFFF) into a2 early and LICM-hoists tile<<6 into s3. */
/* Upload image blocks to VRAM at offsets selected by the tile and block indices. */

void runtime_upload_image_blocks_vram_offsets_selected_tile_block_indices(s32 image_addr, s32 tile_id, s32 num_blocks);

#endif

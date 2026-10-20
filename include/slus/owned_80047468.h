#ifndef SLUS_OWNED_80047468_H
#define SLUS_OWNED_80047468_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_80047270_hdr;

extern void decode_upload_image_from_wrapping_buffer(void *a0, S_80047270_hdr *a1);
extern u16 narrow_texture_pack_x;
extern u16 narrow_texture_pack_y;
extern u16 narrow_texture_pack_column_width;
extern u16 narrow_texture_pack_generation;

typedef struct {
    u8 pad00[4];
    u16 unk04;
    u8 pad06[2];
    s8 unk08;
    s8 unk09;
    u8 unk0A;
    u8 unk0B;
} S_80047468_arg0;

typedef struct {
    u8 pad00[0xC];
    u8 *unk0C;
} S_80047468_arg1;

/* Packs an image into the texture page region at (32, 128), decodes it, and uploads it. */

void pack_texture_into_vram_narrow(S_80047468_arg0 *image, S_80047468_arg1 *source, s32 data_offset);
void func_80047468(S_80047468_arg0 *image, S_80047468_arg1 *source, s32 data_offset);

#endif

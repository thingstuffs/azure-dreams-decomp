#ifndef SLUS_OWNED_80047338_H
#define SLUS_OWNED_80047338_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad0[4];
    u16 unk4;
    u8 pad1[2];
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} S_80047338_hdr;

typedef struct {
    u8 pad0[0xC];
    void *unkC;
} S_80047338_rec;

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_80047270_hdr;

extern void decode_upload_image_from_wrapping_buffer(void *a0, S_80047270_hdr *a1);


extern u16 wide_texture_pack_x;
extern u16 wide_texture_pack_y;
extern u16 wide_texture_pack_column_width;
extern u16 wide_texture_pack_generation;

/* Packs a texture into the atlas, decodes its data, and uploads it to VRAM. */

void pack_texture_into_vram_wide(S_80047338_hdr *texture, S_80047338_rec *record, s32 data_offset);
void func_80047338(S_80047338_hdr *texture, S_80047338_rec *record, s32 data_offset);

#endif

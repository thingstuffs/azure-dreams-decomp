#include "common.h"
#include "engine/graphics.h"
#include "engine/texture.h"
#include "sdk/libgpu.h"
#include "slus/data.h"

/* This whole TU is compiled with -G0 (small-data disabled), so gcc
 * addresses these plain scalars via independent lui/%hi + lw/sw/%lo pairs
 * (no materialised base register reused across accesses), instead of via
 * $gp. D_80080A7C is a plain int elsewhere too (see code5.c func_8004066C,
 * same -G0 TU). D_80081480/D_8008148C are really running write/base
 * pointers into a growing decode buffer, stored as plain 32-bit values. */
extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;

/* Object header this function operates on: rect points at a struct whose
 * fields at 0x4/0x6 are s16 tile-dimension counters. */
typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_8004878C_hdr;

/*
 * Decodes and uploads an image, wrapping the decode buffer when needed.
 *
 * RLE-style byte decoder; only the argument setup (src/dst pointers) needs to match, so declare it
 * minimally.
 */
void decode_compressed_image_to_vram(void *src, S_8004878C_hdr *rect)
{
    s32 pixel_count;
    s32 image_bytes;

    pixel_count = rect->unk04 * rect->unk06;
    image_bytes = pixel_count * 2;
    if ((u32)(gpu_scratch_buffer_base + gpu_scratch_ring_size) <= (u32)(gpu_scratch_write_pointer + pixel_count * 4 + 2)) {
        gpu_scratch_write_pointer = gpu_scratch_buffer_base;
        DrawSync(0);
    }
    decompress_lz(src, (void *)(gpu_scratch_write_pointer + image_bytes));
    texture_handle_expands_six_bit_values_runs_one_four_bytes_until_n_1((u8 *)(gpu_scratch_write_pointer + image_bytes), (u8 *)gpu_scratch_write_pointer);
    LoadImage(rect, (void *)gpu_scratch_write_pointer);
    gpu_scratch_write_pointer = gpu_scratch_write_pointer + image_bytes;
}

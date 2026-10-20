#include "common.h"

/* Running write/base pointers into a growing decode buffer, plain 32-bit
 * scalars accessed via %hi/%lo (not $gp-relative) -- same globals as the
 * sibling decode_compressed_image_to_vram family (same -G0 TU). */
extern s32 gpu_scratch_ring_size;
extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;

/* Object header this function operates on: image_rect points at a struct whose
 * fields at 0x4/0x6 are s16 tile-dimension counters (same shape as the
 * S_8004878C_hdr sibling). */
typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_80047270_hdr;

extern void DrawSync(s32 a0);
extern void *decode_or_copy_resource_pixels(u8 *src_start, u8 *dst_start);
extern int LoadImage(void *rect, void *p);

/* Decodes and uploads an image, wrapping the decode buffer and waiting for the GPU when full. */
void decode_upload_image_from_wrapping_buffer(void *encoded_data, S_80047270_hdr *image_rect)
{
    s32 height_bytes;
    s32 image_bytes;

    height_bytes = image_rect->unk06 * 2;
    image_bytes = image_rect->unk04 * height_bytes;
    if ((u32)(gpu_scratch_buffer_base + gpu_scratch_ring_size) <= (u32)(gpu_scratch_write_pointer + image_bytes)) {
        gpu_scratch_write_pointer = gpu_scratch_buffer_base;
        DrawSync(0);
    }
    decode_or_copy_resource_pixels(encoded_data, (void *)gpu_scratch_write_pointer);
    LoadImage(image_rect, (void *)gpu_scratch_write_pointer);
    height_bytes = image_rect->unk06 * 2;
    image_bytes = image_rect->unk04 * height_bytes;
    gpu_scratch_write_pointer = gpu_scratch_write_pointer + image_bytes;
}

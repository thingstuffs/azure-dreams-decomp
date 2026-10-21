#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "slus/data.h"

typedef struct {
    void *data;
    s16 rect_x;
    s16 rect_y;
    s16 width;
    s16 height;
    s32 unk0C;
} S_8003F8F8;

extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;

/* Uploads a null-terminated image list to VRAM through a staging buffer. */
void decode_and_upload_image_array(S_8003F8F8 *images)
{
    S_8003F8F8 *entry;
    s32 width;
    s32 column_bytes;
    s32 image_bytes;

    entry = images;
    while (entry->data != 0) {
        width = entry->width;
        column_bytes = entry->height * 2;
        image_bytes = width * column_bytes;
        if ((u32)(gpu_scratch_buffer_base + gpu_scratch_ring_size) >=
            (u32)(gpu_scratch_write_pointer + image_bytes)) {
            gpu_scratch_write_pointer = gpu_scratch_buffer_base;
            DrawSync(0);
        }
        decompress_lz(entry->data, (void *)gpu_scratch_write_pointer);
        LoadImage(&entry->rect_x, (void *)gpu_scratch_write_pointer);
        width = entry->width;
        column_bytes = entry->height * 2;
        image_bytes = width * column_bytes;
        entry++;
        gpu_scratch_write_pointer += image_bytes;
    }
}

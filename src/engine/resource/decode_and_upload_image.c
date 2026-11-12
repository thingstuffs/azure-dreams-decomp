#include "common.h"
#include "engine/graphics.h"
#include "engine/resource.h"
#include "sdk/libgpu.h"

#include "sdk/libgpu_types.h"

/* Decompresses image data into an allocated buffer and uploads it to the VRAM rectangle. */
s32 decode_and_upload_image(u8 *compressed_image, RECT *rect) {
    void *image_buf;

    image_buf = alloc_gpu_scratch_ring(rect->w * (rect->h << 1));
    decompress_lz(compressed_image, image_buf);
    return LoadImage(rect, image_buf);
}

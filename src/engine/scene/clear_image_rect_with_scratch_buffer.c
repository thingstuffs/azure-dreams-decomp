#include "common.h"
#include "engine/resource.h"
#include "sdk/libgpu.h"
#include "slus.h"

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s16 unk6;
} S_800404F8;

/* Allocates and zeroes an image buffer, then loads it into the destination rectangle. */
void clear_image_rect_with_scratch_buffer(S_800404F8 *rect) {
    s32 *image_buffer;

    image_buffer = alloc_gpu_scratch_ring((((s16)rect->unk4) >> 1) * rect->unk6);
    zero_words(image_buffer, (((s16)rect->unk4) >> 1) * rect->unk6);
    LoadImage(rect, image_buffer);
}

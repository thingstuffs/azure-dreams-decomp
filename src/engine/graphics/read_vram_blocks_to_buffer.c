#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"

/* PSX libgpu RECT: x,y,w,h as s16 fields. */
typedef struct {
    s16 x, y, w, h;
} RECT_8004B568;

/* D_80081480 / D_8008148C: pointer-valued words (retail neighbours D_80081485 / D_80081490 bound them). */
typedef struct {
    void *field_0;
} S_80081480_8004B568;

typedef struct {
    void *field_0;
} S_8008148C_8004B568;

extern S_80081480_8004B568 gpu_scratch_write_pointer;
extern S_8008148C_8004B568 gpu_scratch_buffer_base;

/*
 * Reads two adjacent VRAM blocks and decodes their data into a buffer at 0x80016000.
 *
 * RLE-style byte decoder; returns the advanced dst pointer ($a1 at exit).
 */
void read_vram_blocks_to_buffer(void)
{
    RECT_8004B568 rect;
    void *decode_dst;
    s16 rect_x;
    s16 rect_w;
    s16 rect_h;
    s16 rect_y;
    s32 block_index;

    decode_dst = (void *)0x80016000;
    DrawSync(0);

    block_index = 0;
    rect_x = 0x140;
    rect_w = 0x40;
    rect_h = 0x80;
    gpu_scratch_write_pointer.field_0 = gpu_scratch_buffer_base.field_0;
    rect_y = 0x100;

    for (; block_index < 2; block_index++) {
        rect.y = rect_y;
        rect.x = rect_x;
        rect.w = rect_w;
        rect.h = rect_h;
        StoreImage(&rect, gpu_scratch_buffer_base.field_0);
        rect_y += 0x80;
        DrawSync(0);
        decode_dst = decompress_lz(gpu_scratch_write_pointer.field_0, decode_dst);
    }
}

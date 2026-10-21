#include "common.h"
#include "engine/resource.h"
#include "sdk/libgpu.h"
#include "slus/data.h"

/* D_80081480 / D_8008148C / D_80080A7C are 4-byte words (retail neighbours D_80081485 /
 * D_80081490 / D_80080A80 bound them). */
extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;

/* Reserves bytes from the buffer's end, resetting its write pointer and waiting for the GPU on overlap. */
s32 reserve_gpu_scratch_tail(s32 byte_count)
{
    s32 reserved_start;
    s32 remaining_size;
    s32 buffer_base;
    s32 buffer_end;

    buffer_base = gpu_scratch_buffer_base;
    buffer_end = buffer_base + gpu_scratch_ring_size;
    if ((u32)(gpu_scratch_write_pointer + byte_count) >= (u32)buffer_end) {
        gpu_scratch_write_pointer = buffer_base;
        DrawSync(0);
    }
    {
        s32 current_base = gpu_scratch_buffer_base;
        remaining_size = gpu_scratch_ring_size;
        reserved_start = current_base + remaining_size;
    }
    reserved_start = reserved_start - byte_count;
    gpu_scratch_ring_size = remaining_size - byte_count;
    return reserved_start;
}

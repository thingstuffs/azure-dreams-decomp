#include "common.h"
#include "engine/resource.h"
#include "sdk/libgpu.h"
#include "slus/gp_af3_pair.h"
#include "slus/data.h"

/* This function's TU is compiled with -G0 (small-data disabled, matching
 * the code5.c / w_8004878C.c family that touches these SAME three globals),
 * so gcc addresses these plain scalars via independent lui/%hi + lw/sw/%lo
 * pairs (no materialised/reused base register), instead of via $gp or an
 * oversized-struct hi/lo forcing trick. */
/* Allocates ring buffer space, wrapping and syncing the GPU when the request reaches the buffer end. */
void *alloc_gpu_scratch_ring(s32 size)
{
    s32 buffer_base = gpu_scratch_buffer_base;

    if ((u32)(buffer_base + gpu_scratch_ring_size) <= (u32)(gpu_scratch_write_pointer + size)) {
        gpu_scratch_write_pointer = buffer_base;
        DrawSync(0);
    }
    {
        void *allocation = (void *)gpu_scratch_write_pointer;
        gpu_scratch_write_pointer = gpu_scratch_write_pointer + size;
        return allocation;
    }
}

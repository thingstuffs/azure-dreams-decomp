#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "sdk/libetc.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/data.h"

extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;

/* Reset callbacks, clear VRAM, and initialize buffer state. */
void reset_callbacks_and_clear_vram(void)
{
    s32 vram_rect[2];

    ResetCallback();
    clear_vram_callback_state();
    init_double_buffered_gpu_environments();
    vram_rect[0] = 0;
    vram_rect[1] = 0x02000400;
    ClearImage(vram_rect, 0, 0, 0);
    gpu_scratch_buffer_base = (s32) gpu_scratch_ring_buffer;
    gpu_scratch_write_pointer = (s32) gpu_scratch_ring_buffer;
    gpu_scratch_ring_size = 0x38000;
}

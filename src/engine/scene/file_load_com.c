#include "common.h"
#include "engine/cd.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "slus.h"


extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;

typedef struct { u32 word; } PackedLoc;

/* Decode a packed ID or relative offset, synchronize, and dispatch the resolved values. */
void file_load_com(void *packed_data_arg)
{
    PackedLoc *packed_data = packed_data_arg;
    s32 id_or_base;
    s32 target_time;
    s32 offset_base;
    s32 id_base;

    DrawSync(0);
    id_or_base = packed_data->word & 0x7FFFFF;
    if (id_or_base == 0) {
        offset_base = gpu_scratch_buffer_base;
        gpu_scratch_write_pointer = offset_base;
        id_or_base = offset_base;
        target_time = id_or_base + ((packed_data->word & 0xFF800000) >> 12);
    } else {
        id_base = gpu_scratch_buffer_base;
        id_or_base = id_or_base | 0x80000000;
        gpu_scratch_write_pointer = id_base;
        target_time = id_base;
    }
    Control_CD(6, packed_data, 0);
    drain_cd_command_queue();
    run_image_load_commands(id_or_base, target_time);
}

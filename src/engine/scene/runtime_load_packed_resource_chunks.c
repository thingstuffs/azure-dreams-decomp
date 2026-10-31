#include "shared/runtime_dispatch.h"
#include "common.h"
#include "engine/cd.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/data.h"

typedef struct Info80046E38 {
    s32 *data;
    u16 count;
} Info80046E38;

typedef struct Pair80046E38 {
    s32 first;
    s32 second;
} Pair80046E38;

extern Info80046E38 *resource_type_list_layouts[];
extern u8 *gpu_scratch_write_pointer;
extern u8 *gpu_scratch_buffer_base[3];


/* Processes the selected entry stream and updates the drawing buffer and mode mask. */
void runtime_load_packed_resource_chunks(s16 entry_id, u8 *stream)
{
    Pair80046E38 pair;
    u8 *stream_start;
    long buffer_start;
    s32 data_offset;
    s32 remaining;
    u8 *table_base;
    s32 table_offset;
    s32 shifted_id;
    Info80046E38 **entry_slot;
    Info80046E38 *entry;
    s32 *entry_data;

    stream_start = stream;
    gpu_scratch_write_pointer = gpu_scratch_buffer_base[0];
    buffer_start = (long)gpu_scratch_buffer_base[0];
    DrawSync(0);

    shifted_id = entry_id << 16;
    table_base = (u8 *)resource_type_list_layouts;
    table_offset = shifted_id >> 14;
    entry_slot = (Info80046E38 **)(table_offset + table_base);
    entry_data = (*entry_slot)->data;
    pair = *(Pair80046E38 *)entry_data;
    entry = *entry_slot;
    remaining = entry->count;
    data_offset = entry->data[1];

    if (remaining > 0) {
        do {
            Control_CD(6, (s32 *)&pair, 0);
            data_offset += 0x10;
            drain_cd_command_queue();
            stream = decompress_lz(gpu_scratch_write_pointer, stream);
            remaining--;
            pack_tagged_resource_descriptor(0x10, 0, (s32 *)&pair, data_offset);
        } while (remaining > 0);
    }

    runtime_set_list_pointers_from_type_offsets(stream_start, entry_id);
    if (runtime_dispatch_state.mode != 2) {
        gpu_scratch_ring_size = 0x8000;
    } else {
        gpu_scratch_ring_size = 0x4000;
    }
    gpu_scratch_write_pointer = (u8 *)((buffer_start + 3) & ~3);
}

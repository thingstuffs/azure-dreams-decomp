#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/resident_resources.h"
#include "engine/cd.h"
#include "engine/scene.h"
#include "slus.h"
#include "slus/data.h"

struct S_8006CE80_ptr
{
    s32 *f0;
    s32 f1;
};
struct S_8006CE80
{
    u16 field0;
    u8 pad2[6];
    struct S_8006CE80_ptr *field8;
};
extern struct S_8006CE80 dispatch_resource_records[];
struct S_8006CE44
{
    s32 field0;
    s32 *field4;
};
extern struct S_8006CE44 scene_resource_group_records[];

extern ResourceReadState scene_geometry[];
extern s32 gpu_scratch_buffer_base;
extern s8 node_update_mode;
extern u8 D_800E6000[];
/* Loads the entry's resource data and selects its working buffer. */
void load_scene_resource_group(s16 entry_index)
{
    struct S_8006CE80 *entry;
    s32 resource_type;
    int request_a[2];
    int request_b[2];
    entry = &dispatch_resource_records[entry_index];
    resource_type = entry->field0;
    node_update_mode = 0;
    scene_geometry[0].field0 = 0;
    if (resource_type != 0) {
        if (resource_type != 4) {
            if (runtime_dispatch_state.mode != resource_type) {
                s32 block_count;
                s32 *resource_info;
                s32 block_offset;
                runtime_dispatch_state.mode = resource_type;
                block_count = scene_resource_group_counts[resource_type];
                resource_info = scene_resource_group_records[resource_type].field4;
                block_offset = 0;
                if ((block_count - 0x200) > 0) {
                    u32 offset_mask;
                    int *next_request;
                    offset_mask = 0x7FFFFF;
                    next_request = request_b;
                    do {
                        pack_tagged_resource_descriptor(0x100, (resource_info[0] & offset_mask) + (block_offset << 11), request_a,
                            resource_info[1] + block_offset);
                        Control_CD(6, request_a, 0);
                        block_offset += 0x100;
                        pack_tagged_resource_descriptor(0x100, (resource_info[0] & offset_mask) + (block_offset << 11), next_request,
                            resource_info[1] + block_offset);
                        Control_CD(6, next_request, 0);
                        drain_cd_command_queue();
                        block_offset += 0x100;
                    }
                    while (block_offset < (block_count - 0x200));
                }
                {
                    u32 packed_info = resource_info[0];
                    block_count = packed_info >> 23;
                    if (block_count != 0) {
                        pack_tagged_resource_descriptor(block_count, (packed_info & 0x7FFFFF) + (block_offset << 11), request_a,
                            resource_info[1] + block_offset);
                        Control_CD(6, request_a, 0);
                    }
                    drain_cd_command_queue();
                }
            }
        }
        else {
            load_shared_resource_once();
            movie_start_sector = *entry->field8->f0;
            movie_frame_control = entry->field8->f1;
        }
    }
    {
        s32 buffer_size;
        s32 buffer_address;
        if (resource_type == 2) {
            buffer_size = 0x18800;
            buffer_address = (s32) (&D_800E6000);
            gpu_scratch_buffer_base = buffer_address;
        }
        else {
            buffer_size = 0x38000;
            buffer_address = (s32) (&gpu_scratch_ring_buffer);
            gpu_scratch_buffer_base = buffer_address;
        }
        gpu_scratch_ring_size = buffer_size;
    }
    runtime_dispatch_state.field_4 = scene_resource_group_records[resource_type].field0;
}

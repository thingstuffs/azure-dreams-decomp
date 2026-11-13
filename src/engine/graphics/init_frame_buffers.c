#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"
#include "engine/graphics.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/gp_af3_pair.h"

typedef u32 OT_TYPE;

typedef struct OrderingTable {
    OT_TYPE ot[0x218];
} OrderingTable;


extern OrderingTable alternate_frame_ordering_table;

/* Initializes frame data and ordering tables, then enables display output. */
void init_frame_buffers(void)
{
    s32 saved_state;

    runtime_dispatch_state.field_0 |= 1;
    saved_state = gpu_scratch_buffer_base;
    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: slus/w_80041A10). */
    do {
        gpu_scratch_write_pointer = saved_state;
    } while (0);
    runtime_reset_object_pool(saved_state);
    reset_scene_frame_callback_list();
    g_game_work.draw_buffer = upper_draw_context;
    ClearOTagR((OT_TYPE *)(upper_draw_context + 0x70), 0x218);
    ClearOTagR(alternate_frame_ordering_table.ot, 0x218);
    {
        u8 *frame_data = g_game_work.draw_buffer;
        *(void **)(frame_data + 0x8D0) = frame_data + 0x8D4;
    }
    SetDispMask(1);
    clear_runtime_slot_word_table();
    set_scene_phase_callback((s32)begin_scene_dispatch_resource_loading);
}

#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "slus.h"

typedef u32 OT_TYPE;

typedef struct FrameData {
    u8 raw[0x8D8];
} FrameData;

typedef struct OrderingTable {
    OT_TYPE ot[0x218];
} OrderingTable;


extern s32 gpu_scratch_buffer_base;
extern s32 gpu_scratch_write_pointer;
extern FrameData upper_draw_context;
extern OrderingTable alternate_frame_ordering_table;

extern void runtime_reset_object_pool(s32);
extern void set_next_scene_phase(void);

/* Initialize frame data and ordering tables and enable the display. */
void init_frame_buffers_for_scene(void)
{
    s32 state_value;
    s32 flags;

    flags = runtime_dispatch_state.field_0;
    flags |= 1;
    runtime_dispatch_state.field_0 = flags;
    state_value = gpu_scratch_buffer_base;
    gpu_scratch_write_pointer = state_value;
    runtime_reset_object_pool(state_value);
    reset_scene_frame_callback_list();
    g_game_work.draw_buffer = (s32)&upper_draw_context;
    ClearOTagR((OT_TYPE *)(upper_draw_context.raw + 0x70), 0x218);
    ClearOTagR(alternate_frame_ordering_table.ot, 0x218);
    {
        u8 *frame_data = (u8 *)((s32)g_game_work.draw_buffer);
        *(void **)(frame_data + 0x8D0) = frame_data + 0x8D4;
    }
    SetDispMask(1);
    clear_runtime_slot_word_table();
    set_scene_phase_callback((s32)set_next_scene_phase);
}

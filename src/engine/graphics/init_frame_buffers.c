#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

typedef u32 OT_TYPE;

typedef struct FrameData {
    u8 raw[0x8D8];
} FrameData;

typedef struct OrderingTable {
    OT_TYPE ot[0x218];
} OrderingTable;


extern s32 D_8008148C;
extern s32 D_80081480;
extern FrameData D_801C9E40;
extern OrderingTable D_801DA784;

extern void runtime_reset_object_pool(s32);
extern void reset_scene_frame_callback_list(void);
extern OT_TYPE *ClearOTagR(OT_TYPE *, s32);
extern void SetDispMask(s32);
extern void clear_runtime_slot_word_table(void);
extern void set_scene_phase_callback(s32);
extern void func_80041AB0(void);

/* Initializes frame data and ordering tables, then enables display output. */
void init_frame_buffers(void)
{
    s32 saved_state;

    D_80082E60.field_0 |= 1;
    saved_state = D_8008148C;
    do {
        D_80081480 = saved_state;
    } while (0);
    runtime_reset_object_pool(saved_state);
    reset_scene_frame_callback_list();
    g_game_work.draw_buffer = (s32)&D_801C9E40;
    ClearOTagR((OT_TYPE *)(D_801C9E40.raw + 0x70), 0x218);
    ClearOTagR(D_801DA784.ot, 0x218);
    {
        u8 *frame_data = (u8 *)((s32)g_game_work.draw_buffer);
        *(void **)(frame_data + 0x8D0) = frame_data + 0x8D4;
    }
    SetDispMask(1);
    clear_runtime_slot_word_table();
    set_scene_phase_callback((s32)func_80041AB0);
}

#include "common.h"
#include "shared/game_work.h"

#include "common.h"
#include "engine/audio.h"
#include "engine/effect.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "engine/texture.h"
#include "sdk/libetc.h"
#include "sdk/libgpu.h"
#include "slus.h"

extern s32 GetRCnt(s32 counter);
extern void ResetRCnt(s32 counter);

extern void update_active_nodes_and_render_frame(void);

extern u8 animation_tick_scale;
extern u8 scene_skip_vsync;
extern s8 last_frame_ticks;
extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;
extern u8 upper_draw_context[];
extern u16 system_update_flags[];

/* Present the frame, switch draw buffers, and synchronize frame timing. */
void render_scene_frame_with_timing(void)
{
    s32 copied_value;
    void *current_buffer;
    u8 *next_buffer;
    void *ordering_table;
    s32 frame_ticks;
    u16 sync_flags;

    PutDispEnv((u8 *)g_game_work.draw_buffer + 0x5C);
    PutDrawEnv(g_game_work.draw_buffer);
    if (!(system_update_flags[0] & 2)) {
        DrawOTag((u8 *)g_game_work.draw_buffer + 0x8CC);
    }
    func_8003E758();
    drain_audio_commands_and_service_channels();
    copied_value = gpu_scratch_buffer_base;
    gpu_scratch_write_pointer = copied_value;
    run_runtime_callbacks();
    update_controller_buttons_and_triggers();

    next_buffer = upper_draw_context;
    current_buffer = g_game_work.draw_buffer;
    if (current_buffer == next_buffer) {
        next_buffer += 0x108D4;
    }
    ordering_table = next_buffer + 0x70;
    g_game_work.draw_buffer = next_buffer;
    ClearOTagR(ordering_table, 0x218);
    *(void **)((u8 *)g_game_work.draw_buffer + 0x8D0) =
        (u8 *)g_game_work.draw_buffer + 0x8D4;
    tick_screen_fade_slots();
    update_active_nodes_and_render_frame();
    if (!(system_update_flags[0] & 2)) {
        DrawSync(0);
    }
    dispatch_and_clear_four_pointer_slots();
    DrawSync(0);
    frame_ticks = GetRCnt(1) + 0xFF;
    sync_flags = system_update_flags[0];
    frame_ticks >>= 8;
    last_frame_ticks = (s8)frame_ticks;
    if (!(sync_flags & 2)) {
        if (scene_skip_vsync == 0) {
            VSync((animation_tick_scale != 1) * 2);
        }
    }
    ResetRCnt(1);
}

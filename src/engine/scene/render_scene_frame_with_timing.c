#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

#include "engine/audio.h"
#include "engine/effect.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "engine/texture.h"
#include "sdk/libetc.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/scene_frame_data.h"
#include "slus/gpu_scratch_data.h"
#include "slus/animation_tick_data.h"
#include "sdk/libapi.h"
#include "dungeon/player.h"



extern u16 system_update_flags[];

/* Present the frame, switch draw buffers, and synchronize frame timing. */
void render_scene_frame_with_timing(void)
{
    s32 copied_value;
    void *current_buffer;
    GpuContext *next_buffer;
    void *ordering_table;
    s32 frame_ticks;
    u16 sync_flags;

    PutDispEnv(&g_game_work.draw_buffer->disp);
    PutDrawEnv(&g_game_work.draw_buffer->draw);
    if (!(system_update_flags[0] & 2)) {
        DrawOTag(&g_game_work.draw_buffer->orderTag[0x218 - 1]);
    }
    service_cd_command_queue();
    drain_audio_commands_and_service_channels();
    copied_value = gpu_scratch_buffer_base;
    gpu_scratch_write_pointer = copied_value;
    run_frame_callbacks();
    update_controller_buttons_and_triggers();

    next_buffer = upper_draw_context;
    current_buffer = g_game_work.draw_buffer;
    if (current_buffer == next_buffer) {
        next_buffer++;
    }
    ordering_table = next_buffer->orderTag;
    g_game_work.draw_buffer = next_buffer;
    ClearOTagR(ordering_table, 0x218);
    g_game_work.draw_buffer->packetCursor = g_game_work.draw_buffer->packets;
    tick_screen_fade_slots();
    update_active_nodes_and_render_frame();
    if (!(system_update_flags[0] & 2)) {
        DrawSync(0);
    }
    flush_sprite_resource_slots();
    DrawSync(0);
    frame_ticks = GetRCnt(1) + 0xFF;
    sync_flags = system_update_flags[0];
    frame_ticks >>= 8;
    last_frame_ticks = (u8)frame_ticks;
    if (!(sync_flags & 2)) {
        if (scene_skip_vsync == 0) {
            VSync((animation_tick_scale != 1) * 2);
        }
    }
    ResetRCnt(1);
}

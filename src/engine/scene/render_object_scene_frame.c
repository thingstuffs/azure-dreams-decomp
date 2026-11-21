#include "common.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "engine/audio.h"
#include "engine/effect.h"
#include "engine/node.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "engine/texture.h"
#include "sdk/libetc.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/animation_tick_data.h"
#include "slus/gpu_scratch_data.h"
#include "slus/scene_frame_data.h"

/* Draw the current frame, swap draw buffers, and wait for optional vertical synchronization. */
void render_object_scene_frame(void)
{
    u8 *next_buffer;

    PutDispEnv((u8 *)g_game_work.draw_buffer + 0x5C);
    PutDrawEnv(g_game_work.draw_buffer);
    DrawOTag((u8 *)g_game_work.draw_buffer + 0x8CC);
    service_cd_command_queue();
    drain_audio_commands_and_service_channels();
    gpu_scratch_write_pointer = gpu_scratch_buffer_base;
    run_frame_callbacks();
    update_controller_buttons_and_triggers();
    next_buffer = upper_draw_context;
    if (g_game_work.draw_buffer == next_buffer) {
        next_buffer += 0x108D4;
    }
    g_game_work.draw_buffer = next_buffer;
    ClearOTagR((u32 *)(next_buffer + 0x70), 0x218);
    {
        GpuContext *frame = g_game_work.draw_buffer;
        frame->packetCursor = (u8 *)frame + 0x8D4;
    }
    tick_screen_fade_slots();
    update_active_nodes();
    flush_sprite_resource_slots();
    DrawSync(0);
    if (!scene_skip_vsync) {
        VSync(animation_tick_scale == 1 ? 0 : 2);
    }
}

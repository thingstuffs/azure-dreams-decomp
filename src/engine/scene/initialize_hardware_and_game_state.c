#include "common.h"
#include "shared/game_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_floor.h"
#include "shared/runtime_dispatch.h"
#include "shared/object_flags.h"
#include "engine/audio.h"
#include "engine/entity.h"
#include "engine/input.h"
#include "engine/scene.h"
#include "sdk/libc.h"
#include "sdk/libcd.h"
#include "sdk/libetc.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "slus/data.h"
#include "slus.h"
#include "sdk/libapi.h"

/* short globals D_80080A94/98/9C read via %hi/%lo; accessed via fixed
 * absolute-address casts (see D_80013180 group note below) so gcc reuses the
 * base==dest lbu/lhu macro form the retail binary shows for each (a solitary
 * hi/lo read immediately consumed as a call arg). */


/*
 * Initialize video, CD, pads, graphics, configuration defaults, and stream state.
 *
 * D_80012094, D_80012098, D_80012D6E, D_80013180, D_80013184, D_80013186 all share the same %hi()
 * page (0x8001xxxx) in the retail binary and are accessed off ONE materialised base register
 * across this whole block, despite being far apart -- so the retail source used fixed absolute
 * addresses here (like the established `bzero((void*)0x80013564, ...)` idiom elsewhere in this
 * codebase), letting gcc CSE/constant-fold the shared %hi at compile time instead of via 6
 * independent extern symbols.
 *
 * mirror/shadow copies of the same three D_80013180-group fields
 */
void initialize_hardware_and_game_state(void)
{
    GpuContext **stream_slot = &g_game_work.draw_buffer;
    s32 pad_byte;
    GpuContext *stream_state;

    SetVideoMode(0);
    CdInit();
    reset_cd_command_retry_state();
    ResetGraph(0);
    init_audio_subsystem();

    sound_set_cd_playback_volume_scale(*(s16 *)0x80080A94);
    sound_set_sequence_volume_scale(*(s16 *)0x80080A98);
    sound_set_voice_gain_scale(*(s16 *)0x80080A9C);

    for (pad_byte = 0; pad_byte < PAD_REPLY_LENGTH; pad_byte++) {
        controller_port_one_reply[pad_byte] = 0xFF;
        controller_port_two_reply[pad_byte] = 0xFF;
    }
    InitPAD(controller_port_one_reply, PAD_REPLY_LENGTH, controller_port_two_reply, PAD_REPLY_LENGTH);

    StartPAD();
    initialize_memory_card_services(1);
    SetGraphDebug(0);
    InitGeom();

    runtime_dispatch_state.field_B = 0;
    bzero(&floor_generation_state, sizeof(floor_generation_state));

    reset_game_state_preserving_session_fields();

    {
        u32 config_word = 0x2A080808;
        u8 config_byte4, config_byte6;

        GAME_STATE->options.option_color = config_word; /* D_80013180 */
        *(u32 *)0x80081494 = config_word;
        config_byte4 = 0x20;
        GAME_STATE->options.unk_3184 = config_byte4; /* D_80013184 */
        *(u8 *)0x800814AC = config_byte4;
        config_byte6 = 3;
        GAME_STATE->options.unk_3186 = config_byte6; /* D_80013186 */
        *(u8 *)0x800814A4 = config_byte6;
        GAME_STATE->familiar_direction[0] = 5;   /* D_80012094 */
        GAME_STATE->message_speed = 0;    /* D_80012D6E */
        GAME_STATE->familiar_ai_mode[0] = 2;   /* D_80012098 */
    }
    build_cubic_cumulative_table();

    stream_state = upper_draw_context;
    if (*stream_slot == upper_draw_context) {
        stream_state = stream_state + 1;
    }
    *stream_slot = stream_state;
    stream_state->packetCursor = stream_state->packets;
    default_textured_quad_color[0] = 0x2C808080;
    reset_scene_sprite_history();

    {
        u32 *buffer_ptrs = frame_packet_limit_pointers;
        *buffer_ptrs = (u32)D_801D8D7A;
        buffer_ptrs[1] = (u32)D_801E964E;
    }
}

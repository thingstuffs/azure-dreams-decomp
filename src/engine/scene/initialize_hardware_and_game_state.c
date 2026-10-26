#include "common.h"
#include "shared/object_flags.h"
#include "engine/audio.h"
#include "engine/entity.h"
#include "engine/scene.h"
#include "sdk/libc.h"
#include "sdk/libcd.h"
#include "sdk/libetc.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "slus/data.h"

extern s32 InitPAD(u8 *buf1, s32 siz1, u8 *buf2, s32 siz2);

extern void initialize_memory_card_services(s32 a0);
extern void sound_set_cd_playback_volume_scale(s16 volume_scale);
extern void sound_set_voice_gain_scale(s16 a0);

extern void reset_cd_command_retry_state(void);
extern void StartPAD(void);

/* D_80083160[0] holds the current CD/streaming state pointer; default value is
 * the sentinel D_801C9E40. size>8 to force %hi/%lo. */
extern void *D_80083160[3];
extern u32 default_textured_quad_color[3];

/* short globals D_80080A94/98/9C read via %hi/%lo; accessed via fixed
 * absolute-address casts (see D_80013180 group note below) so gcc reuses the
 * base==dest lbu/lhu macro form the retail binary shows for each (a solitary
 * hi/lo read immediately consumed as a call arg). */

/* pad-buffer arrays passed to InitPAD */
extern u8 controller_port_one_reply[0x22];
extern u8 controller_port_two_reply[0x22];

extern u8 floor_generation_state[8];
extern u8 scene_mode_code[];

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
    void **stream_slot = D_80083160;
    s32 pad_byte;
    u8 *stream_state;

    SetVideoMode(0);
    CdInit();
    reset_cd_command_retry_state();
    ResetGraph(0);
    init_audio_subsystem();

    sound_set_cd_playback_volume_scale(*(s16 *)0x80080A94);
    sound_set_sequence_volume_scale(*(s16 *)0x80080A98);
    sound_set_voice_gain_scale(*(s16 *)0x80080A9C);

    for (pad_byte = 0; pad_byte < 0x22; pad_byte++) {
        controller_port_one_reply[pad_byte] = 0xFF;
        controller_port_two_reply[pad_byte] = 0xFF;
    }
    InitPAD(controller_port_one_reply, 0x22, controller_port_two_reply, 0x22);

    StartPAD();
    initialize_memory_card_services(1);
    SetGraphDebug(0);
    InitGeom();

    scene_mode_code[0] = 0;
    bzero(floor_generation_state, 8);

    reset_game_state_preserving_session_fields();

    {
        u8 *config_base = (u8 *)0x80010000;
        u32 config_word = 0x2A080808;
        u8 config_byte4, config_byte6;

        *(u32 *)(config_base + 0x3180) = config_word; /* D_80013180 */
        *(u32 *)0x80081494 = config_word;
        config_byte4 = 0x20;
        *(u8 *)(config_base + 0x3184) = config_byte4; /* D_80013184 */
        *(u8 *)0x800814AC = config_byte4;
        config_byte6 = 3;
        *(u8 *)(config_base + 0x3186) = config_byte6; /* D_80013186 */
        *(u8 *)0x800814A4 = config_byte6;
        *(s16 *)(config_base + 0x2094) = 5;   /* D_80012094 */
        *(u8 *)(config_base + 0x2D6E) = 0;    /* D_80012D6E */
        *(s16 *)(config_base + 0x2098) = 2;   /* D_80012098 */
    }
    build_cubic_cumulative_table();

    stream_state = upper_draw_context;
    if (*stream_slot == upper_draw_context) {
        stream_state = stream_state + 0x108D4;
    }
    *stream_slot = stream_state;
    *(u32 *)(stream_state + 0x8D0) = (u32)(stream_state + 0x8D4);
    default_textured_quad_color[0] = 0x2C808080;
    initialize_runtime_table_defaults();

    {
        u32 *buffer_ptrs = frame_packet_limit_pointers;
        *buffer_ptrs = (u32)D_801D8D7A;
        buffer_ptrs[1] = (u32)D_801E964E;
    }
}

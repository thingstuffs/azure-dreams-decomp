#include "common.h"
#include "m2c_compat.h"

void play_movie_with_fixed_display_flag(s32 table_index, s32 flags);
void file_load_com(void *packed_data);
short SD_Call(int flags);
void drain_audio_commands_and_service_channels(void);
s32 func_80066F78(s32);
extern s8 scene_music_hold;
extern u32 town_scene_resource_descriptor[2];
extern u32 D_800D1D54[2];

/* Sets the global flag, runs the setup sequence, and processes both global data blocks. */
void set_global_flag_runs_setup(void) {
    scene_music_hold = 1;
    SD_Call(0x7F);
    drain_audio_commands_and_service_channels();
    SD_Call(0x60C);
    drain_audio_commands_and_service_channels();
    play_movie_with_fixed_display_flag(0x13, 0xC6);
    func_80066F78(1);
    file_load_com(town_scene_resource_descriptor);
    file_load_com(D_800D1D54);
}

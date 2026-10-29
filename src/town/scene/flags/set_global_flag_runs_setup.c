#include "common.h"
#include "m2c_compat.h"
#include "engine/audio.h"
#include "engine/movie.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "town/scene/flags.h"

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
    SetDispMask(1);
    file_load_com(town_scene_resource_descriptor);
    file_load_com(D_800D1D54);
}
